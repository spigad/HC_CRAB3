#!/usr/bin/perl
#
use Getopt::Long;
use File::Temp qw/tempfile tmpnam/;
use File::Basename;
use Date::Parse;
use Date::Format;

# Format strings
$maxhn = 25;
$eventtable = "%s&%s&%s\n";

$logfile = $ARGV[0];

@info = &parseinfo($logfile);

# Loop on events for the job
for (my $i = 0; $i <= $info[0]; $i++) {
    next unless (&debugfilter($i));
    printf $eventtable,
    ${$info[1]}[$i],
    ${$info[11]}[$i] || '',
    ${$info[14]}[$i] || '';
}

sub debugfilter {
    my $i = shift;
    my $useful = 0;
    my $event = ${$info[1]}[$i];
    my $reason = ${$info[11]}[$i];
    my $result = ${$info[10]}[$i] || ${$info[13]}[$i] || '';
    my $src = ${$info[3]}[$i] || '';
    if ($event eq 'Transfer' and $src eq 'LM' and $reason ne 'GLBS_OK' and $reason ne 'unavail') {
	$useful = 1;
    } elsif ($event eq 'Done' and $result ne 'OK' and $reason ne 'COND_ERR') {
	$useful = 1;
    } elsif ($event eq 'Abort' and $reason ne 'RETRY_EX') {
	$useful = 1;
    }
    return $useful;
}

sub creason {
    my $reason = shift;
    my $type = shift;
    my %Reasons = ('Job successfully submitted to Globus' => ['GLBS_OK', 0],
		   'unavailable'                          => ['unavail', 0],
		   '\(nil\)'                              => ['(nil)', 0],
		   'Job terminated successfully'          => ['JOB_OK', 0],
		   'Warning: job exit code \!= 0'         => ['EXIT_NE_0', 1],
		   'Job got an error while in the CondorG queue' =>
		   ['COND_ERR', 0],
		   'hit job retry count'                  => ['RETRY_EX', 0],
		   'Job RetryCount'                       => ['RETRY_EX', 0],
		   'hit job shallow retry count'          => ['SHRTY_EX', 0],
		   'Got a job held event, reason: Failed to get expiration time of proxy' => ['FAIL_EXP', 1],
		   'Got a job held event, reason.*The job attribute PeriodicHold expression .*Matched.*TRUE' => ['PER_HOLD', 1],
		   'token still exists'                   => ['TOK_EXIS', 0],
		   'Cannot plan: BrokerHelper: no compatible resources' =>
		   ['NO_RES', 1],
		   'There were some warnings: some file\(s\) listed in the output sandbox were not available and were ignored' => ['MISS_OUT', 0],
		   'Got a job held event, reason: Globus error 158: the job manager could not lock the state lock file' => ['GLBS_158', 1],
		   '7:* authentication failed: GSS Major Status: Authentication Failed GSS Minor Status Error Chain:  init.c:499: globus_gss_assist_init_sec_context_async: Error during context initialization init_sec_context' =>
		   ['AUTH_FAI', 1],
		   'authentication failed: GSS Major Status: Unexpected Gatekeeper or Service Name GSS Minor Status Error Chain:  init.c:499: globus_gss_assist_init_sec_context_async: Error during context initialization' =>
		   ['UNEXP_SN', 1],
		   'mkfifo .*: File exists' => ['MKFIFO', 1],
		   'Problems during rank evaluation \(e\.g\. GRISes down, wrong JDL rank expression, etc\.\)' => ['NO_MATCH', 1],
		   'Aborted by user' => ['ABORT_US', 0],
		   'X509 proxy expired' => ['PROXY_EX', 1],
                   'request expired' => ['REQ_EXP', 1],
		   'Cannot read JobWrapper output, both from Condor and from Maradona' => ['MARADONA', 1],
		   '37.* the provided RSL \'queue\' parameter is invalid' =>
		   ['GLBS_37', 1],
		   '156.* the job contact string does not match any which the job manager is handling' => ['GLBS_156', 1],
		   'reason: via condor_hold \(by user root\)' => ['COND_HLD', 1],
		   '8 the user cancelled the job' => ['GLBS_8', 1],
		   '8: the user cancelled the job' => ['GLBS_8', 1],
		   'Cancelled by user' => ['USR_CANC', 0],
		   'Cancel requested by WorkloadManager' => ['WM_CANC', 0],
		   'Cannot take token!' => ['NO_TOKEN', 0],
                   'no matching resources found' => ['NO_MATCH', 1],
		   'BrokerHelper: no compatible resources' => ['NO_COMP', 1],
                   'Cannot take token for https' => ['NO_TOKE2', 1],
		   'Cannot upload .+ into .+' => ['NO_UPLOD', 1],
		   'Cannot download .+ from .+' => ['NO_DWLOD', 1],
		   'Job has been terminated by the batch system' =>
		   ['JOB_TERM', 1],
		   'Got a job held event, reason: Unspecified gridmanager error' => ['GRIDMGR', 1],
		   'Job successfully submitted over the Grid' => ['JOB_OK', 0],
		   'LM message: the timeout attached to the globus-down event expired' => ['GDETOEXP', 1],
		   'Removal entries exceeded' => ['REEN_EXC', 1],
                   'Removal retries exceeded' => ['RERE_EXC', 1],
		   'the job manager failed to create the temporary stdout filename' => ['GLBS_69', 1],
		   'the job manager failed to create the temporary stderr filename' => ['GLBS_70', 1],
		   'data transfer to the server failed' => ['GLBS_10', 1],
		   'Got a job held event, reason: Repeated submit attempts \(GAHP reports:\)' => ['MANY_SUB', 1],
		   'Got a job held event, reason: Globus error 75: the cache file could not be opened in order to relocate the user proxy' => ['GLBS_75', 1],
		   'Got a job held event, reason: Repeated submit attempts \(GAHP reports:Job not found\)' => ['MANY_SU2', 1],
		   'Got a job held event, reason: Attempts to submit failed' => ['SUB_FAIL', 1],
		   'Got a job held event, reason: Globus error 28: the job manager failed to create an internal script submission file' => ['GLBS_28', 1],
		   'Got a job held event, reason: Globus error 5: the executable does not exist' => ['GLBS_5', 1],
		   'an authentication operation failed' => ['GLBS_7', 1],
		   'Got a job held event, reason: Globus error 12: the connection to the server failed \(check host and port\)' => ['GLBS_12', 1],
		   'Got a job held event, reason: Globus error 9: the system cancelled the job' => ['GLBS_9', 1],
		   'Got a job held event, reason: Globus error 128: could not write the remote io url file' => ['GLBS_128', 1],
		   'Got a job held event, reason: Globus error 43: the job manager failed to stage the executable' => ['GLBS_43', 1],
		   '43 the job manager failed to stage the executable' => ['GLBS_43', 1],
		   'Got a job held event, reason: Globus error 21: the job manager failed to locate an internal script argument file' => ['GLBS_21', 1],
		   'Got a job held event, reason: Globus error 94: the jobmanager does not accept any new requests \(shutting down\)' => ['GLBS_94', 1],
		   '22 the job manager failed to create an internal script argument file' => ['GLBS_22', 1],
		   'Got a job held event, reason: Globus error 24: the job manager detected an invalid script response' => ['GLBS_24', 1],
		   'the gatekeeper failed to run the job manager' =>
		   ['GLBS_47', 1],
		   'Got a job held event, reason: Globus error 79: connecting to the job manager failed.  Possible reasons: job terminated, invalid job contact, network problems,' => ['GLBS_79', 1],
		   'Got a job held event, reason: Globus error 10: data transfer to the server failed' => ['GLBS_10', 1],
		   'Got a job held event, reason: Job removed from batch queue manually' => ['JOB_REMO', 1],
		   'Got a job held event, reason: Globus error 124: old job manager is still alive' => ['GLBS_124', 1],
		   'Got a job held event, reason: Globus error 3: an I/O operation failed' => ['GLBS_3', 1],
		   '3 an I/O operation failed' => ['GLBS_3', 1],
		   '17.* the job failed when the job manager attempted to run it' => ['GLBS_17', 1],
		   'NORDUGRID_SUBMIT timed out' => ['NG_SUBTO', 1],
		   '121.* the job state file doesn\'t exist'  => ['GLBS_121', 1],
		   '126.* it is unknown if the job was submitted'  => ['GLBS_126', 1],
		   '127.* the provided RSL \'remote_io_url\' parameter is invalid'  => ['GLBS_127', 1],
		   'Got a job held event, reason: Globus error 131: the user proxy expired \(job is still running\)' => ['GLBS_131', 1],
		   'globus-user-env.sh not found or unreadable' => ['ENV_NOFD', 1],
                   'Failed to create a delegation id for job' => ['FAIL_DEL', 1],
                   'Cannot move ISB' => ['NO_ISB', 1],
                   'Job Aborted because proxy expired' => ['PROXY_EXP', 1],
                   'Got a job held event, reason: Job failed, no reason given by GRAM server' => ['JOB_FAIL', 1],
                   'CREAM Register raised' => ['CREAM_EX', 1],
                   'CREAM Register returned error' => ['CREAM_ER', 1],
                   'CREAM Start raised exception' => ['CREAM_ST', 1],
                   'Got a job held event, reason: Globus error 25: the job manager detected an invalid script status' => ['GLBS_25', 1],
                   'The job cannot be submitted because the blparser service is not alive' => ['BLPRS_ER', 1],
                   'reason=999' => ['ERR_999', 1],
                   'reason=1' => ['ERR_1', 1],
                   'reason=127' => ['ERR_127', 1],
                   'reason=271' => ['ERR_271', 1],
                   'Proxy expired' => ['PROX_EXP', 1],
                   'Working directory not writable' => ['WKDIR_NA', 1],
                   'BLAH error: submission command failed' => ['BLAH_FAI', 1],
                   'BLAH error: no jobId in submission script' => ['BLAH_NID', 1],
                   'LB query failed' => ['LBQRY_FL', 1],
                   'Cannot find grid-proxy-info' => ['NO_PXINF', 1]
		   );
    
    my $code = 'UNKNOWN';
    if ( ! defined $type || $type != 1 ) {
	foreach ( keys %Reasons ) {
	    if ( $reason =~ /$_/ ) {
		$code = ${$Reasons{$_}}[0];
	    }
	}
	return ($code, $reason);
    } else {
	foreach my $ref ( values %Reasons ) {
	    if ( $code eq ($ref->[0] || '') ) {   # da aggiustare
		return $ref->[1];
	    }
	}
    }
}

sub component {
    my $comp = shift;
    my %Components = (
		      UserInterface   => UI,
		      NetworkServer   => NS,
		      WorkloadManager => WM,
		      BigHelper       => BH,
		      JobController   => JC,
		      LogMonitor      => LM,
		      LRMS            => LR
		      );
    return $Components{$comp} || $comp;
}

sub parseinfo {
    my $temp = shift;

# Parse the logging info
    my @event = ();
    my @time = ();
    my @source = ();
    my @from = ();
    my @dest = ();
    my @desthost = ();
    my @destid = ();
    my @host = ();
    my @node = ();
    my @result = ();
    my @reason = ();
    my @fullreason = ();
    my @exitcode = ();
    my @statuscode = ();
    open(LOG, "$temp") or die "Cannot open logging info file\n";
    my $ev = -1;
    while ( <LOG> ) {
	chomp;
	if (/Event:/ ) {
	    $ev++;
	    $event[$ev] = $time[$ev] = $source[$ev] = $from[$ev] =
		$dest[$ev] = $desthost[$ev] = $destid[$ev] = $host[$ev] =
		$node[$ev] = $result[$ev] = $reason[$ev] = $exitcode[$ev] =
		$statuscode[$ev] = '';
	}
	next unless ($ev+1);
	$event[$ev]      = $1 if (/Event: (\w+)/);
	$time[$ev]       = str2time($1) if ( /imestamp\s*=\s*(.+)/ );
	$source[$ev]     = &component($1) if ( /ource\s*=\s*(\w+)$/ );
	$from[$ev]       = &component($1) if ( /from\s*=\s*(.+)/ );
	$dest[$ev]       = &component($1) if ( /estination\s*=\s*(.+)/ );
	$desthost[$ev]   = $1 if ( /est.host\s*=\s*(.+)/ );
	$destid[$ev]     = $1 if ( /est.id\s*=\s*(.+)/ );
	$host[$ev]       = $1 if ( /\b.ost\s*=\s*(.+)/ );
	$node[$ev]       = $1 if ( /node\s*=\s*(.+)/ );
	$result[$ev]     = $1 if ( /esult\s*=\s*(.+)/ );
	($reason[$ev], $fullreason[$ev]) = &creason($1) if ( /eason\s*=\s*(.+)/ );
	$exitcode[$ev]   = $1 if ( /xit..ode\s*=\s*(.+)/ );
	$statuscode[$ev] = $1 if ( /tatus..ode\s*=\s*(.+)/ );
    }
    close LOG;
    return ($ev, \@event, \@time, \@source, \@from, \@dest, \@desthost,
	    \@destid, \@host, \@node, \@result, \@reason, \@exitcode,
	    \@statuscode, \@fullreason);
}

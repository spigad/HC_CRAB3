#!/usr/bin/python

import sys
import re
import optparse
import glob
import xml.parsers.expat

job_failed = False
fjr_exception = False
fjr_error = ''

# Print error messages found
def print_errors(errors):

    for line in errors:
        print line

# Function to find wrapper errors not coming from cmsRun
# All lines between 'cmsRun started' and 'cmsRun ended' are ignored
def wrapper_errors(joboutput):

    errors = []
    p = re.compile('ERROR|Sandbox too big|eval')
    p1 = re.compile('started at')
    p2 = re.compile('ended at')
    incms = False
    for line in joboutput:
        if p1.search(line):
            incms = True
        if p2.search(line):
            incms = False
        if incms:
            continue
        if p.search(line):
            errors.append(line)

    return ''.join(errors)

def fjr_start(name, attr):

    global job_failed, fjr_exception
    if name == 'FrameworkJobReport':
        status = attr['Status']
        if status == 'Success':
            job_failed = False
        else:
            job_failed = True
    elif name == 'FrameworkError':
        type = attr['Type']
        if type == 'CMSException':
            fjr_exception = True

def fjr_end(name):

    global fjr_exception
    if name == 'FrameworkError':
        fjr_exception = False

def fjr_cdata(data):

    global fjr_error, fjr_exception
    p1 = re.compile(r'[\w]+')
    p2 = re.compile(r'^\s*(.+)')
    if fjr_exception:
        if p1.search(data):
            fjr_error = fjr_error + p2.search(data).group(1) + '\n'

# Function to find CMSSW errors in the FJR
def fjr_errors(jobfjr):

    global fjr_error
    errors = []
    
    p = xml.parsers.expat.ParserCreate()
    p.StartElementHandler = fjr_start
    p.EndElementHandler = fjr_end
    p.CharacterDataHandler = fjr_cdata
    p.Parse(jobfjr, 1)
    fjr_errors = fjr_error[0:-1]
    return fjr_errors

# Extract exit codes
def exit_codes(joboutput):

    exe_exitstatus = -1
    job_exitstatus = -1
    p1 = re.compile('EXECUTABLE_EXIT_STATUS = (.+)')
    p2 = re.compile('JOB_EXIT_STATUS = (.+)')
    for line in joboutput:
        if p1.search(line):
            exe_exitstatus = p1.search(line).group(1)
        if p2.search(line):
            job_exitstatus = p2.search(line).group(1)

    return int(exe_exitstatus), int(job_exitstatus)

def run(jobdir=None, jobid=''):

    if jobdir is None:
        parser = optparse.OptionParser(description='Extract error information from job output.')
        #parser.add_argument('jobdir')
        (_, args) = parser.parse_args()
        try:
          jobdir = args[0]
        except:
          return None

    stdouts = glob.glob(jobdir + '/*%s.stdout' % str(jobid))
    if stdouts:
        stdout = stdouts[0]
    else:
        return None
    fjrs = glob.glob(jobdir + '/*fjr*%s.xml' % str(jobid))
    fjr = ''
    if fjrs:
        fjr = fjrs[0]
        f = open(fjr)
        jobfjr = f.read()

    f = open(stdout)
    output = f.readlines()
    f.close()

    (exe_code, job_code) = exit_codes(output)
    errors = None

    if exe_code == 0 and job_code == 0:
        return None
    else:
        errors = ''
        if fjr:
            errors = fjr_errors(jobfjr)
        else:
            errors = wrapper_errors(output)
        #print errors
    return (exe_code, job_code, errors)

if __name__ == "__main__":
    try:
        (exe_code, job_code, errors) = run()
        print exe_code, job_code
        if errors:
            print errors
    except:
        pass

# Extract exit codes from stdout
# EXECUTABLE_EXIT_STATUS = n or
# ExeExitCode=n
# JOB_EXIT_STATUS = m or
# JobExitCode=m
# If they are both zero, exit
# If at least one is not zero, look if FJR exists
# If it does not exist, parse stdout for errors
# If it exists, extract exit codes from it and check that they correspond (TODO)
# If they do not, complain and exit (TODO)
# Check that the Status is Failed and if not, complain and exit (TODO)
# Parse FJR for error strings
# If found, print them and exit
# If not found, complain and parse stdout for errors (TODO)
# If no errors found in stdout, complain and exit (TODO)

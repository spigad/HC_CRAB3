"""Experimental way to setup cronjobs for the HC crontab scheduler.

Each of the lines represent a cronjob, with the format:
 frequency (in minutes) : [ list of cronjobs to execute ]
Each app must defie a module like this as app.cron_settings with the CRONJOBS
attribute defined.
The scheduler, hc.core.crontab.scheduler will run the method run() of an
instance of a class named app.crontab.jobs.<cron>.Cron, being <cron> the name
of the cronjob set in the list, in the example, hello and cron.
"""

#TODO(rmedrano): Move to this schema or remove this crap.


CRONJOBS = {
            '5': ['hello', 'cron']
}

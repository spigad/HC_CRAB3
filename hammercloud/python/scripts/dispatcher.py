#!/usr/bin/env python

from django.conf import settings
from scripts.actions import CronActions
import getopt
import logging
import os
import sys

"""Dispatcher for the crontab actions available for HammerCloud.

Launches the proper action from the available actions and collects the argument
for the callee.
"""

SHORT_OPS = 'f:o:t:m:h'
LONG_OPS = ['days=', 'doit']


def print_usage():
    """Prints usage."""
    functions = [func for func in dir(CronActions) if not func.startswith('_')]
    print '''List of allowed options
    -f : Set the function you want to execute. Below, allowed functions.
             %s
    -h : Print help. ''' % '\n             '.join(functions)


def run(dic):
    """Run the selected action by -f."""
    ca = CronActions()
    installed_apps = [app.split('.')[1] for app in settings.INSTALLED_APPS
                                            if app.startswith('hc')]

    if '-h' in dic:
        print_usage()
    elif '-f' in dic:
        if not 'APP' in os.environ:
            logging.error('The application is not defined in the environment')
            print_usage()
            return 1
        app = os.environ['APP']

        if not app in installed_apps:
            logging.error('The application name is not valid')
            print_usage()
            return 2
        else:
            getattr(ca, dic['-f'])(app, dic)
            return 0
    else:
        logging.error('Missing funcion name (-f)')
        print_usage()
        return 3


if __name__ == '__main__':
    try:
        dic = {}
        opts, _ = getopt.getopt(sys.argv[1:], SHORT_OPS, LONG_OPS)
        for opt, arg in opts:
            dic[opt] = arg
        sys.exit(run(dic))
    except getopt.GetoptError, err:
        print err
        print_usage()
        sys.exit(4)

#!/usr/bin/env python

import os
import subprocess
import sys

"""Bootstrap script to set up the Python environment

Should be called after the virtualenv is activated in order to install all the
Python modules and dependencies in the local venv. This work has been greatly
inspired by the following Colin Copeland's article: http://goo.gl/KIMsq
"""


def main():
    if 'VIRTUAL_ENV' not in os.environ:
        # TODO(rmedrano): One could enable the virtualenv programatically.
        print >> sys.stderr, '$VIRTUAL_ENV not found, please enable one.'
        return -1
    base_path = os.path.dirname(__file__)
    return subprocess.call(['pip', 'install', '--upgrade', '--requirement',
                            os.path.join(base_path, 'requirements/apps.txt')])


if __name__ == '__main__':
    sys.exit(main())

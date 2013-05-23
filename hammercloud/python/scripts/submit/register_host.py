from hc.core.utils.generic.class_func import custom_import
import commands
import logging

"""Action to register the current load of the machine.

The load allows to schedule tests in different machines to balance the resource
usage.
"""


class RegisterHost(object):

    def run(self, app, dic, alpha=0.4):
        """To calculate the load, an exponential smoothing is used."""
        Host = custom_import('hc.%s.models.Host' % app)
        hostname = commands.getoutput('hostname')
        load = float(commands.getoutput("cat /proc/loadavg | awk '{print $1}'"))

        host = Host.objects.get(name=hostname)
        if host:
            host.loadavg1m = host.loadavg1m * (1.0 - alpha) + load * alpha
            host.save()
            logging.info('Inserted new load for %s: %f (new value: %f)',
                         hostname, host.loadavg1m, load)
            return True
        else:
            logging.error('Unknown host: %s', hostname)
            return False

#!/bin/sh

# Script to restart all the services needed for HammerCloud in a row.
# Does not need any environment setup.

/etc/init.d/varnish stop
/etc/init.d/httpd stop
/etc/init.d/memcached stop
/etc/init.d/memcached start
/etc/init.d/httpd start
/etc/init.d/varnish start

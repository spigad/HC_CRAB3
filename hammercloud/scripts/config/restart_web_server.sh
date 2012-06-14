#!/bin/sh

/etc/init.d/varnish stop
/etc/init.d/httpd stop
/etc/init.d/memcached stop
/etc/init.d/memcached start
/etc/init.d/httpd start
/etc/init.d/varnish start

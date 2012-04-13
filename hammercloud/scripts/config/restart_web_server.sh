#!/bin/sh

/etc/init.d/varnish stop
/etc/init.d/httpd restart
/etc/init.d/varnish start

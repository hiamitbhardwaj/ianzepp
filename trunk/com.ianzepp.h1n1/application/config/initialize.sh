#!/bin/bash

#
# This script initializes the site
#

H1N1_BASE="/mnt/h1n1/app"
H1N1_SITE="com.ianzepp.h1n1"

# Copy over the site config
cp -f "${H1N1_BASE}/${H1N1_SITE}/application/config/site.config" "/etc/apache2/sites-available/${H1N1_SITE}"

# Disable and reenable the site
a2dissite "default"
a2dissite "${H1N1_SITE}"
a2ensite  "${H1N1_SITE}"

# Restart apache
/etc/init.d/apache2 restart

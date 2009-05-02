#!/bin/bash

#
# This initializes the system
#

apt-get -y -q install apache2-mpm-prefork libapache2-mod-php5 php5
apt-get -y -q install mysql-server php5-mysql  
apt-get -y -q autoremove

#
# Import the mysql migrations
#

for MIGRATION in `ls "${H1N1_BASE}/${H1N1_SITE}/migration/pdo_mysql/*.sql" | sort`;
do
	echo ${MIGRATION};
done

exit

#
# This initializes the site
#

H1N1_BASE="/mnt"
H1N1_SITE="com.ianzepp.h1n1"

# Copy over the site config
cp -f "${H1N1_BASE}/${H1N1_SITE}/application/config/site.config" "/etc/apache2/sites-available/${H1N1_SITE}"

# Disable and reenable the site
a2dissite "default"
a2dissite "${H1N1_SITE}"
a2ensite  "${H1N1_SITE}"
a2enmod   "rewrite"
a2enmod   "php5"

# Restart apache
/etc/init.d/apache2 restart

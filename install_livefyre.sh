#!/bin/bash

if [[ -z $1 ]]; then
    echo "usage: $0 BLOGNAME TYPE"
    echo "   eg: $0 drupaltest (community or enterprise)"
    exit 1
fi

if [[ -z $2 ]]; then
    echo "usage: $0 BLOGNAME TYPE"
    echo "   eg: $0 drupaltest (community or enterprise)"
    exit 1
fi

BLOGNAME=$1 
if [[ $2 = 'enterprise' ]]; then
    PLUGINNAME='livefyre-enterprise-drupal.zip'
else
    PLUGINNAME='livefyre-drupal.zip'
fi

./build.sh $2

scp $PLUGINNAME root@orangesaregreat.com:/var/www/orangesaregreat.com/$BLOGNAME/sites/all/modules

sleep 1

ssh root@orangesaregreat.com "cd /var/www/orangesaregreat.com/$BLOGNAME/sites/all/modules; unzip $PLUGINNAME; rm $PLUGINNAME"
#!/bin/bash

if [[ -z $1 ]]; then
    echo "usage: $0 BLOGNAME"
    echo "   eg: $0 drupaltest"
    exit 1
fi

BLOGNAME=$1 

./build.sh

scp livefyre-drupal.tar.gz root@orangesaregreat.com:/var/www/orangesaregreat.com/$BLOGNAME/sites/all/modules

sleep 1

ssh root@orangesaregreat.com "cd /var/www/orangesaregreat.com/$BLOGNAME/sites/all/modules; tar xvfz livefyre-drupal.tar.gz; rm livefyre-drupal.tar.gz"
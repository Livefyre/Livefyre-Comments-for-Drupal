#!/bin/bash

./build.sh

scp livefyre-drupal.tar.gz root@orangesaregreat.com:/var/www/orangesaregreat.com/drupaltest/sites/all/modules

sleep 1

ssh root@orangesaregreat.com 'cd /var/www/orangesaregreat.com/drupaltest/sites/all/modules; tar xvfz livefyre-drupal.tar.gz; rm livefyre-drupal.tar.gz'
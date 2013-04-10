#!/bin/bash

rm livefyre-drupal.tar.gz
cd livefyre
tar --exclude='.git/' -zcvf livefyre-drupal.tar.gz livefyre*
mv livefyre-drupal.tar.gz ..
cd ..

echo "
*Made a new zip file for you: livefyre-drupal.tar.gz"

#!/bin/bash

cd livefyre
tar cvzf livefyre-drupal.tar.gz livefyre* js README.txt
mv livefyre-drupal.tar.gz ..
cd ..

echo "
*Made a new zip file for you: livefyre-drupal.tar.gz"

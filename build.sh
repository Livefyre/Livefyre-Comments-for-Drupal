#!/bin/bash

if [[ -z $1 ]]; then
    echo "Must supply a customer (enterprise/community)"
    exit 1
fi

# Decides which system we are on and what sed to run
IS_BSD=$([ "$(uname -s)" == "Darwin" ] && echo 1)
function sed_i () {
    if [ ${IS_BSD} ]; then
        sed -i '' "$@"
    else
        sed -i "$@"
    fi
}

cd livefyre
if [[ $1 = 'enterprise' ]]; then
    PLUGINNAME='livefyre-enterprise-drupal.tar.gz'
    echo "Making an Enterprise Drupal Plugin!"
    sed_i '/\/\/ Enterprise Hook/a\
        \        include "livefyre-enterprise-code.inc";' livefyre.module
    sed_i '/\/\/ Enterprise Hook/a\
        \    include "livefyre-enterprise-settings.inc";' livefyre.admin.inc
else
    echo "Making a Community Drupal Plugin!"
    PLUGINNAME='livefyre-drupal.tar.gz'
fi
rm $PLUGINNAME
tar --exclude='.git/' --exclude='settings-toggle.js' -zcvf $PLUGINNAME livefyre*
mv $PLUGINNAME ..
if [[ $1 = 'enterprise' ]]; then
    echo "Reverting Enterprise Changes!"
    sed_i 's/        include "livefyre-enterprise-code.inc";//g' livefyre.module
    sed_i 's/    include "livefyre-enterprise-settings.inc";//g' livefyre.admin.inc
else
    echo "No enterprise reverting necessary!"
fi
cd ..

echo "
*Made a new zip file for you: $PLUGINNAME"

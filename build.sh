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

PATHROOT=$( cd $(dirname $0) ; pwd -P )
mkdir "$PATHROOT/temp_build"
cp -r "$PATHROOT/livefyre" "$PATHROOT/temp_build/"
TEMPPATH="$PATHROOT/temp_build"
SRCPATH="$TEMPPATH/livefyre-comments/src"

if [[ $1 = 'enterprise' ]]; then
    PLUGINNAME='livefyre-enterprise-drupal.zip'
    echo "Making an Enterprise Drupal Plugin!"
    sed_i '/\/\/ Enterprise Hook/a\
        \        include "livefyre-enterprise-code.inc";' "$TEMPPATH/livefyre/livefyre.module"
    sed_i '/\/\/ Enterprise Hook/a\
        \    include "livefyre-enterprise-settings.inc";' "$TEMPPATH/livefyre/livefyre.admin.inc"
else
    echo "Making a Community Drupal Plugin!"
    PLUGINNAME='livefyre-drupal.zip'
fi
rm $PLUGINNAME
zip -r $PLUGINNAME livefyre -x ".git/" -x "/livefyre/livefyre-api/.git/*" -x "settings-toggle.js"
rm -rf $TEMPPATH

echo "
*Made a new zip file for you: $PLUGINNAME"

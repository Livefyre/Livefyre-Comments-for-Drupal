<?php

function livefyre_admin($form, &$form_state) {

    $form = array();

    $form['livefyre_network'] = array(
        '#type' => 'textfield',
        '#title' => t('Livefyre Network'),
        '#default_value' => variable_get('livefyre_network', 'livefyre.com'),
        '#description' => t("Livefyre Network. Do not change unless on a custom network."),
        '#required' => TRUE,
    );

    $form['livefyre_network_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Livefyre Network Key'),
        '#default_value' => variable_get('livefyre_network_key', '5X32DydAyfYFUvHPC6gTp4xNjHw='),
        '#description' => t("Livefyre Network Key. Do not change unless on a custom network."),
        '#required' => TRUE,
    );

    $form['livefyre_site_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Livefyre Site ID'),
        '#default_value' => variable_get('livefyre_site_id'),
        '#description' => t("The site ID supplied by Livefyre."),
        '#required' => TRUE,
    );

    $form['livefyre_site_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Livefyre Site Key'),
        '#default_value' => variable_get('livefyre_site_key'),
        '#description' => t("The Site Key supplied by Livefyre."),
        '#required' => TRUE,
    );

    $form['livefyre_app_config'] = array(
        '#type' => 'textarea',
        '#title' => t('Livefyre Application Configuration'),
        '#description' => t("Set a JSON string to be used for your whole Livefyre configuration. Parts may be overwritten when declared below."),
        '#default_value' => variable_get('livefyre_app_config', ''),
        '#resizable' => TRUE,
        '#rows' => 5,
    );

    $form['livefyre_auth_delegate'] = array(
        '#type' => 'textarea',
        '#title' => t('Livefyre Authenticaton Delegate'),
        '#description' => t("Set the Authentication Delegate for Livefyre. This will override 'delegate' in the App configuration. This function must return an auth delegate variable built according to the following: <a href='https://github.com/Livefyre/livefyre-docs/wiki/Comments-3-Integration-Guide#wiki-single-sign-on'> Livefyre Single Sign On</a>"),
        '#default_value' => variable_get('livefyre_auth_delegate', ''),
        '#resizable' => TRUE,
        '#rows' => 5,
    );

    $form['livefyre_conv_load_callback'] = array(
        '#type' => 'textarea',
        '#title' => t('Livefyre Conversation Load Callback'),
        '#description' => t("Set the function to call back to when the widget loads. This will override 'onload' in the App configuration."),
        '#default_value' => variable_get('livefyre_conv_load_callback', ''),
        '#resizable' => TRUE,
        '#rows' => 5,
    );

    $form['livefyre_custom_css'] = array(
        '#type' => 'textarea',
        '#title' => t('Livefyre Custom CSS'),
        '#description' => t("Add custom CSS to your Livefyre Comment Widget. This CSS will appear inline on the page. Please use only Livefyre specific adjustments or rules will be applied to non-Livefyre tags."),
        '#default_value' => variable_get('livefyre_custom_css', ''),
        '#resizable' => TRUE,
        '#rows' => 5,
    );

    $form['livefyre_node_types'] = array(
        '#type' => 'checkboxes',
        '#default_value' => variable_get('livefyre_node_types', array()),
        '#title' => t('Display Livefyre on:'),
        '#description' => t('Livefyre will only be displayed on the selected node types above.'),
        '#options' => node_type_get_names(),
    );

    return system_settings_form($form);
}

function livefyre_admin_validate($form, &$form_state) {

    $lf_site_id = $form_state['values']['livefyre_site_id'];
    $lf_json = $form_state['values']['livefyre_app_config'];
    $lf_auth_delegates = $form_state['values']['livefyre_auth_delegate'];

    if (!is_numeric($lf_site_id)) {
        form_set_error('livefyre_site_id', t('Your site ID needs to be an integer.'));
    }

    if (!is_valid_json($lf_json) && $lf_json != '') {
        form_set_error('livefyre_app_config', t('The Livefyre Application Configuratin is not valid JSON'));
    }

}

function is_valid_json($str) {
    
    if (json_decode($str, $assoc = TRUE) == NULL) {
        return FALSE;
    }

    return TRUE;

}

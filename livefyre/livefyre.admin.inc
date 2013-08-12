<?php

/**
 * Implements hook_admin().
 * @param array $form
 *   The form for validation.
 * @param array $form_state
 *   The state the form is in.
 * @return
 *   Settings form.
 */
function livefyre_admin($form, &$form_state) {

  $form = array();

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

  /* The Enterprise Hook is used to build the plugin to either include
   * enterprise level functionality. Without this comment, things will not
   * build nicely and sed will most likely break.
   */
  // Enterprise Hook
  

  $form['livefyre_node_types'] = array(
    '#type' => 'checkboxes',
    '#default_value' => variable_get('livefyre_node_types', array()),
    '#title' => t('Display Livefyre on:'),
    '#description' => t('Livefyre will only be displayed on the selected node types above.'),
    '#options' => node_type_get_names(),
  );

  return system_settings_form($form);
}

// /**
//  * Implements hook_validate().
//  * @param array $form
//  *   The form for validation.
//  * @param array $form_state
//  *   The state the form is in.
//  */
// function livefyre_admin_validate($form, &$form_state) {

//   $lf_site_id = $form_state['values']['livefyre_site_id'];
//   $lf_json = $form_state['values']['livefyre_app_config'];
//   $lf_auth_delegates = $form_state['values']['livefyre_auth_delegate'];

//   if (!is_numeric($lf_site_id)) {
//     form_set_error('livefyre_site_id', t('Your site ID needs to be an integer.'));
//   }

//   if (!is_valid_json($lf_json) && $lf_json != '') {
//     form_set_error('livefyre_app_config', t('The Livefyre Application Configuratin is not valid JSON'));
//   }

// }

/**
 * Helper: Validates JSON data.
 * @param string
 *   String to check for validity.
 * @return
 *   Validity of the JSON.
 */
function is_valid_json($str) {
    
  if (json_decode($str, $assoc = TRUE) == NULL) {
    return FALSE;
  }

  return TRUE;

}

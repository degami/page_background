<?php

/**
 * @file
 * Page Background Views Integration views.inc.
 */

/**
 * Implements hook_views_data().
 */
function page_background_views_integration_views_data() {
  $data['url_background_images']['table']['group'] = t('Page Backgrounds');
  $data['url_background_images']['table']['base'] = array(
    // This is the identifier field for the view.
    'field' => 'bid',
    'title' => t('Page Backgrounds'),
    'help' => t('Page Background Stores Paths Background Images.'),
    'weight' => -10,
  );

  $data['url_background_images']['table']['join'] = array(
    'file_managed' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  // Example numeric text field.
  $data['url_background_images']['bid'] = array(
    'title' => t('Page Background Bid'),
    'help' => t('Page Background Bid'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['url_background_images']['fid'] = array(
    'title' => t('Page Background Image'),
    'help' => t('Page Background Image.'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'PageBackgroundImageHandlerFieldImage',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Has Image'),
      'type' => 'yes-no',
    ),
    'relationship' => array(
      'base' => 'file_managed',
      'base field' => 'fid',
      'handler' => 'views_handler_relationship',
      'label' => t('Image file'),
      'title' => t('The file associated with this image.'),
      'help' => t('Access to the file information associated with this image.'),
    ),
  );

  $data['url_background_images']['path'] = array(
    'title' => t('Page Background Path'),
    'help' => t('Page Background Path.'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['url_background_images']['weight'] = array(
    'title' => t('Page Background Weight'),
    'help' => t('Page Background Weight'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['url_background_images']['created'] = array(
    'title' => t('Page Background Creation Timestamp'),
    'help' => t('Page Background Creation Timestamp'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['url_background_images']['bglinkurl'] = array(
    'title' => t('Page Background LinkUrl'),
    'help' => t('Page Background LinkUrl.'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['url_background_images']['bgtext'] = array(
    'title' => t('Page Background Slogan Text'),
    'help' => t('Page Background Slogan Text.'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['url_background_images']['image_alt'] = array(
    'title' => t('Page Background Image Alt Tag'),
    'help' => t('Page Background Image Alt Tag.'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['url_background_images']['image_title'] = array(
    'title' => t('Page Background Image Title Tag'),
    'help' => t('Page Background Image Title Tag.'),
    'group' => t('Page Backgrounds'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function page_background_views_integration_views_data_alter(&$data) {
  $data['node']['page_background'] = array(
    'title' => t('Node Page Backgrounds'),
    'help' => t('Node Page Backgrounds'),
    'group' => t('Page Backgrounds'),
    'relationship' => array(
      // Table we're joining to.
      'base' => 'url_background_images',
      // Field on the joined table.
      'base field' => 'path',
      // Real field name on the 'node' table.
      'field' => 'nid',
      'handler' => 'PageBackgroundViewsIntegrationViewsHandlerRelationship',
      'label' => t('Page Backgrounds'),
      'title' => t('Page Backgrounds'),
    ),
  );

  $data['taxonomy_term_data']['page_background'] = array(
    'title' => t('Taxonomy Term Page Backgrounds'),
    'help' => t('Taxonomy Term Page Backgrounds'),
    'group' => t('Page Backgrounds'),
    'relationship' => array(
      // Table we're joining to.
      'base' => 'url_background_images',
      // Field on the joined table.
      'base field' => 'path',
      // Real field name on the 'taxonomy_term_data' table.
      'field' => 'tid',
      'handler' => 'PageBackgroundViewsIntegrationViewsHandlerRelationship',
      'label' => t('Page Backgrounds'),
      'title' => t('Page Backgrounds'),
    ),
  );
}

/**
 * Implements hook_views_handlers().
 */
function page_background_views_integration_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'page_background_views_integration'),
    ),
    'handlers' => array(
      'PageBackgroundImageHandlerFieldImage' => array(
        'parent' => 'views_handler_field',
      ),
      'PageBackgroundViewsIntegrationViewsHandlerRelationship' => array(
        'parent' => 'views_handler',
      ),
    ),
  );
}

<?php

/**
 * @file
 * Definition of page_background_image_handler_field_image.
 */

/**
 * Field handler to provide simple renderer that allows using a themed image.
 *
 * @ingroup views_field_handlers
 */
class PageBackgroundImageHandlerFieldImage extends views_handler_field {

  /**
   * Option_definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['image_style'] = array('default' => '');
    return $options;
  }

  /**
   * Default options.
   *
   * form that provides the label widget that all fields should have.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $styles = image_styles();
    $style_options = array('' => t('Default'),'original' => t('Original image'));
    foreach ($styles as $style) {
      $style_options[$style['name']] = $style['name'];
    }

    $form['image_style'] = array(
      '#title' => t('Image style'),
      '#description' => t('Using <em>Default</em> will display the image fid.'),
      '#type' => 'select',
      '#options' => $style_options,
      '#default_value' => $this->options['image_style'],
    );
  }

  /**
   * Render.
   */
  public function render($values) {
    if ($this->options['image_style'] && module_exists('image')) {
      if ($picture_fid = $this->get_value($values)) {
        $picture = file_load($picture_fid);
        $picture_filepath = $picture->uri;
      }
      if (file_valid_uri($picture_filepath)) {
        if ($this->options['image_style'] != 'original') {
          $output = theme('image_style', array(
            'style_name' => $this->options['image_style'],
            'path' => $picture_filepath,
          ));
        }
        else {
          $output = theme('image', array('path' => $picture_filepath));
        }
      }
      else {
        $output = '';
      }
    }
    else {
      // @todo default output if no imagestyle selected.
      $output = $this->get_value($values);
    }

    return $output;
  }
}

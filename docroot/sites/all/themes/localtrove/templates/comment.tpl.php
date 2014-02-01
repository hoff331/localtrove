<?php

?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print $picture ?>

  <?php if ($new): ?>
    <span class="new"><?php print $new ?></span>
  <?php endif; ?>

  <?php print render($title_prefix); ?>
  <h4<?php print $title_attributes; ?>><?php print $title ?></h4>
  <?php print render($title_suffix); ?>

  <div class="submitted">
    <!--<?php print $permalink; ?>-->
    <?php print $submitted; ?>
  </div>

  <div class="content"<?php print $content_attributes; ?>>
    <p><?php
      // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
    ?></p>
    <?php if ($signature): ?>
    <div class="user-signature clearfix">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
  </div>

  <?php print render($content['links']) ?>
</div>

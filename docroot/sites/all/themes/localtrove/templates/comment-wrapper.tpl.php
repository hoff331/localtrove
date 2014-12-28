<?php

?>
<div id="comments" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if ($content['comments'] && $node->type != 'forum'): ?>
    <?php print render($title_prefix); ?>
    <h2 class="title"><?php print t('Comments'); ?></h2>
    <?php print render($title_suffix); ?>
  <?php endif; ?>

  <?php print render($content['comments']); ?>

<?php if ( (isset($node) && $node->type == 'fairs') || (isset($node) && $node->type == 'farmers_market') || (isset($node) && $node->type == 'art_fair') || (isset($node) && $node->type == 'flee_market') ) : ?>
  <?php if ($content['comment_form']): ?>
    <h2 class="title comment-form"><?php print t('Rate and Review this event'); ?></h2>
    <?php print render($content['comment_form']); ?>
  <?php endif; ?>
<?php elseif (isset($node) && $node->type == 'vendor') : ?>
  <?php if ($content['comment_form']): ?>
    <h2 class="title comment-form"><?php print t('Contact vendor'); ?></h2>
    <div class="description">Comments left here are private and are only visibile to the vendor.</div>
    <?php print render($content['comment_form']); ?>
  <?php endif; ?>
<?php else: ?>
  <?php if ($content['comment_form']): ?>
    <h2 class="title comment-form"><?php print t('Add new comment'); ?></h2>
    <?php print render($content['comment_form']); ?>
  <?php endif; ?>
<?php endif; ?>
</div>

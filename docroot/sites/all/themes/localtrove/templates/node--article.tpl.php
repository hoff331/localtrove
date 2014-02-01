<?php if ($teaser): ?>
    <div class="listing contextual-links-region">
        <div class="listingLeft">
            <?php if (isset($content['field_image'])): ?>
                <?php print render($content['field_image']); ?>
            <?php endif; ?>
        </div>
        <div class="listingRight">
            <?php print render($title_prefix); ?>
            <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
            <?php print render($title_suffix); ?>
            
            <?php if ($display_submitted): ?>
                <div class="articleSubmitted">
                    <?php print $submitted; ?>
                </div>
            <?php endif; ?>
                    
            <?php if (isset($content['body'])): ?>
                <?php print render($content['body']); ?>
            <?php endif; ?>
            
            <?php if (isset($content['field_tags'])): ?>
                <h6>Tags:</h6><?php print render($content['field_tags']); ?>
            <?php endif; ?>
            
            <!--<a href="<?php print $node_url; ?>">read more</a>-->
            
            <?php print render($content['links']); ?>
            <?php print render($content['comments']); ?>
        </div>
        <div class="clearfix"></div>
    </div>
    
<?php else: ?>
    
	<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

	<?php print $user_picture; ?>

	<?php if(!$page && !$teaser) :?>
		<?php print render($title_prefix); ?>
        <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
        <?php print render($title_suffix); ?>
    <?php endif; ?>
    
	<?php if ($display_submitted): ?>
        <div class="submitted">
            <?php print $submitted; ?>
        </div>
    <?php endif; ?>

    <div class="content"<?php print $content_attributes; ?>>
        <?php
            // We hide the comments and links now so that we can render them later.
            hide($content['comments']);
            hide($content['links']);
            print render($content);
        ?>
    </div>

    <?php print render($content['links']); ?>
    <?php print render($content['comments']); ?>
    
    </div>
<?php endif; ?>
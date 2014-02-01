<?php

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

	<?php print $user_picture; ?>

	<?php print render($title_prefix); ?>
	<?php if ($teaser): ?>
        <div class="listing contextual-links-region">
            <div class="listingLeft">
                <?php if (isset($content['field_item_for_sale_image'])): ?>
                    <?php print render($content['field_item_for_sale_image']); ?>
                <?php endif; ?>
            </div>
            <div class="listingRight">
                <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
                <!--IFS-->
                <?php if (isset($content['field_item_for_sale_price'])): ?>
                    <h6>Price of Item:</h6><?php print render($content['field_item_for_sale_price']); ?>
                <?php endif; ?>
                <?php if (isset($content['field_item_for_sale_type'])): ?>
                    <h6>Type of Item:</h6><?php print render($content['field_item_for_sale_type']); ?>
                <?php endif; ?>
                
                <a href="<?php print $node_url; ?>">more information</a>
                
                <?php print render($content['links']); ?>
                <?php print render($content['comments']); ?>
            </div>
            <div class="clearfix"></div>
        </div>
        <?php print render($title_suffix); ?>
	<?php else: ?>
		<?php print render($title_suffix); ?>
    
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
    <?php endif; ?>

</div>
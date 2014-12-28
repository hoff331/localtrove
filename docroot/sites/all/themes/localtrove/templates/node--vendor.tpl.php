<?php if ($teaser): ?>
    <div class="listing contextual-links-region
		<?php if (isset($content['field_vendor_coupon'])): ?>
            <?php echo(" couponListing"); ?>
        <?php endif; ?>">
        <div class="listingLeft">
            <?php if (isset($content['field_vendor_logo'])): ?>
                <?php print render($content['field_vendor_logo']); ?>
            <?php endif; ?>
        </div>
        <div class="listingRight">
            <?php print render($title_prefix); ?>
            <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
            <?php print render($title_suffix); ?>
            
            <!--Vendors-->
            <?php if (isset($content['field_vendor_coupon'])): ?>
                <div id="couponIcon"></div>
            <?php endif; ?>
            <?php if (isset($content['field_vendor_products'])): ?>
                <h6>Type of Products:</h6><?php print render($content['field_vendor_products']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_payments_accepted'])): ?>
                <h6>Payments Accepted:</h6><?php print render($content['field_payments_accepted']); ?>
            <?php endif; ?>
            
            <a href="<?php print $node_url; ?>">more information</a>
            
            <!--Remove php print render Links/Comments-->
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
    <!--added because private comments removes default commend header
    <h2 class="title comment-form">Contact vendor</h2>
    <div class="description">Comments left here are private and are only visibile to the vendor.</div>
    <?php print render($content['comments']); ?>
    
    </div>
<?php endif; ?>

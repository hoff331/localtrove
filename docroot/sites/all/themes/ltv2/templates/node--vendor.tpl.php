<?php if ($teaser): ?>
    <?php if ($promote): ?>
	<!-- if teaser and promoted -->
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
            <div>Promoted Node Teaser</div>
            <!--Vendors-->
            <?php if (isset($content['field_vendor_coupon'])): ?>
                <div id="couponIcon"><?php print render($content['field_vendor_coupon']); ?></div>
			<?php endif; ?>
            <?php if (isset($content['field_vendor_products'])): ?>
                <h6>Type of Products:</h6><?php print render($content['field_vendor_products']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_payments_accepted'])): ?>
                <h6>Payments Accepted:</h6><?php print render($content['field_payments_accepted']); ?>
            <?php endif; ?>
            
            <a href="<?php print $node_url; ?>">more information</a>
            
            <!-- Remove php print render Links/Comments-->
        </div>
        <div class="clearfix"></div>
    </div>
	<?php else: ?>
	<!-- if teaser and NOT promoted -->
	<div class="listing contextual-links-region">
        <div class="listingLeft">
            <?php if (isset($content['field_vendor_logo'])): ?>
                <?php print render($content['field_vendor_logo']); ?>
            <?php endif; ?>
        </div>
        <div class="listingRight">
            <?php print render($title_prefix); ?>
            <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
            <?php print render($title_suffix); ?>
            
            <!-- Vendors-->
            <?php if (isset($content['field_vendor_products'])): ?>
                <h6>Type of Products:</h6><?php print render($content['field_vendor_products']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_payments_accepted'])): ?>
                <h6>Payments Accepted:</h6><?php print render($content['field_payments_accepted']); ?>
            <?php endif; ?>
            
            <a href="<?php print $node_url; ?>">more information</a>
            
            <!-- Remove php print render Links/Comments-->
        </div>
        <div class="clearfix"></div>
    </div>
	<?php endif; ?>
	
<?php else: ?>
    
	<?php if($promote): ?>
	<!--promoted content view-->
		<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
	
		<?php print $user_picture; ?>
	
		<?php print render($title_prefix); ?>
			<h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
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
		<!--added because private comments removes default comment header-->
		<h2 class="title comment-form">Contact vendor</h2>
		<div class="description">Comments left here are private and are only visibile to the vendor.</div>
		<?php print render($content['comments']); ?>
		
		</div>
	<?php else: ?>
	<!-- NOT promoted content view-->
		<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
	
		<?php print $user_picture; ?>
	
		<?php print render($title_prefix); ?>
			<h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
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
				// hide contact fields, featured listing only
				hide($content['field_vendor_facebook']);
				hide($content['field_vendor_twitter']);
				hide($content['field_vendor_pinterest']);
				hide($content['field_vendor_etsy']);
				hide($content['field_vendor_website']);
				print render($content);
			?>
		</div>
	
		<?php print render($content['links']); ?>
		<!-- added because private comments removes default comment header-->
		<h2 class="title comment-form">Contact vendor</h2>
		<div class="description">Comments left here are private and are only visibile to the vendor.</div>
		<?php print render($content['comments']); ?>
		
		</div>
	<?php endif; ?>
		
<?php endif; ?>
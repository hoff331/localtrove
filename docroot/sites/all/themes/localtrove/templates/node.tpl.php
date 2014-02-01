<?php

?>
<?php if ($teaser): ?>
    <div class="listing">
        <div class="listingLeft">
            <?php if (isset($content['field_farmers_market_marker'])): ?>
                <?php print render($content['field_farmers_market_marker']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_flee_market_marker'])): ?>
                <?php print render($content['field_flee_market_marker']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_auction_marker'])): ?>
                <?php print render($content['field_auction_marker']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_art_fair_marker'])): ?>
                <?php print render($content['field_art_fair_marker']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_garage_sale_marker'])): ?>
                <?php print render($content['field_garage_sale_marker']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_estate_sale_marker'])): ?>
                <?php print render($content['field_estate_sale_marker']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_fairs_marker'])): ?>
                <?php print render($content['field_fairs_marker']); ?>
            <?php endif; ?>
        </div>
        <div class="listingRight">
            <?php print render($title_prefix); ?>
            <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
            <?php print render($title_suffix); ?>
    
            <!--Events-->
            <?php if (isset($content['field_rating'])): ?>
                <?php print render($content['field_rating']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_date'])): ?>
                <?php print render($content['field_date']); ?>
            <?php endif; ?>
            <!--Event Marker Swap-->
            <?php if (isset($content['field_event_address'])): ?>
                <?php print render($content['field_event_address']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_farmers_market_address'])): ?>
                <?php print render($content['field_farmers_market_address']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_flee_market_address'])): ?>
                <?php print render($content['field_flee_market_address']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_auction_address'])): ?>
                <?php print render($content['field_auction_address']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_art_fair_address'])): ?>
                <?php print render($content['field_art_fair_address']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_garage_sale_address'])): ?>
                <?php print render($content['field_garage_sale_address']); ?>
            <?php endif; ?>
            <?php if (isset($content['field_estate_sale_address'])): ?>
                <?php print render($content['field_estate_sale_address']); ?>
            <?php endif; ?>
            
            <a href="<?php print $node_url; ?>">more information</a>
            
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
        <!--
        <?php if( ($type == "art_fair") || ($type == "auction") || ($type == "estate_sale") || ($type == "fairs") || ($type == "farmers_market") || ($type == "flee_market") || ($type == "garage_sale") ): ?>
            <?php if( ($uid == 1) || ($uid == 75) || ($uid == 97) ): ?>
            <div id="eventClaim">
                <a href="/claim-event">Claim this Event</a>
            </div>
            <?php endif; ?>
        <?php endif; ?>
        -->
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
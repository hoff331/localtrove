<?php

?>

<div id="headerWrapper">
	<div id="header">
    	<div id="headerLeft">
        	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" height="90" width="312" /></a>
        </div>
        <div id="headerRight"><!--floats right -->
            <ul class="menu">
            	<li><a href="/vendor-registration">Vendor<br/>Registration</a></li>
            </ul>
        </div>
        <div id="headerMiddle">
			<?php print render($page['headerRight']); ?>
        </div>
        <div class="clearfix"></div>
    </div>
</div>

<div id="navigationWrapper">
	<div id="navigation">
        <div id="navigationLeft">
        	<?php print render($page['navigation']); ?>
        </div>
        <div id="navigationRight">
        	<div id="search">
            	<?php print render($page['search']); ?>
            </div>
        </div>
        <div class="clearfix"></div>
    </div>
</div><!--end navigationWrapper-->


<div id="eventsNavWrapper">
	<div id="eventsNav">
        <?php print render($page['eventsNav']); ?>
        <div class="clearfix"></div>
    </div>
</div><!--end eventsNavWrapper-->


<div id="contentWrapper">
	<div id="intContent">
    	<!--if subNav, feature and nearbyMap print intContentLeft with class notFull-->
		<div id="intContentLeft"
		<?php if ($page['subNav'] || $page['feature'] || $page['addEvent'] || $page['nearbyMap']): ?>
        <?php echo("class='notFull'"); ?>
        <?php endif; ?>
        >
        		<?php if ($breadcrumb): ?>
					<?php print $breadcrumb; ?>
				<?php endif; ?>
                <?php print render($title_prefix); ?>
				<?php if ($title): ?>
					<h1><?php print $title; ?></h1>
				<?php endif; ?>
				<?php print render($title_suffix); ?>
                <?php print $messages; ?>
				<?php if ($tabs = render($tabs)): ?>
					<div class="tabs"><?php print $tabs; ?></div>
				<?php endif; ?>
				<?php print render($page['help']); ?>
				<?php if ($action_links): ?>
					<ul class="action-links"><?php print render($action_links); ?></ul>
				<?php endif; ?>
                <?php print render($page['content']); ?>
        </div>
        
        <!--if subNav, feature or nearbyMap print intContentRight-->
		<?php if ($page['subNav'] || $page['feature'] || $page['addEvent'] || $page['nearbyMap']): ?>
        <div id="intContentRight">
        	
			<?php if ($page['subNav']): ?>
            <div id="subNav">
				<?php print render($page['subNav']); ?>
			</div>
            <?php endif; ?>
            
            <?php if ($page['addEvent']): ?>
            <div id="feature">
				<?php print render($page['addEvent']); ?>
			</div>
            <?php endif; ?>
            
			<?php if ($page['feature']): ?>
            <div id="feature">
				<?php print render($page['feature']); ?>
			</div>
            <?php endif; ?>
            
            <?php if ($page['nearbyMap']): ?>
            <div id="nearbyMap">
				<?php print render($page['nearbyMap']); ?>
			</div>
            <?php endif; ?>
            
        </div>
        <?php endif; ?>
    			
    
        <div class="clearfix"></div>
    </div>
</div>

<div id="footerWrapper">
    <div id="footer">
    	<div id="footerLeft1"><?php print render($page['footerLeft1']); ?></div>
        <div id="footerLeft2"><?php print render($page['footerLeft2']); ?></div>
        <div id="footerLeft3"><?php print render($page['footerLeft3']); ?></div>
        <div id="footerRight"><?php print render($page['footerRight']); ?></div>
        <div class="clearfix"></div>
    </div>
</div>

<div id="copyWrapper">
    <div id="copy">
    	<div id="copyLeft">
    	<?php print render($page['copyLeft']); ?>
	</div>
        <div id="copyCenter"></div>
        <div id="copyRight">
	<?php print render($page['copyRight']); ?>
	</div>
    	<div class="clearfix"></div>
    </div>
</div>

<div id="vendorRegistrationWrapper">
	<aside id="vendorRegistration">
		<?php print render($page['vendorReg']); ?>
	</aside>
	<div id="vendorRegistrationFlag">
		<ul class="menu">
			<li><a href="#">Vendor<br/>Registration</a></li>
		</ul>
	</div>
</div>


<div id="navigationWrapper">
	<nav id="navigation">
        <div id="navigationLeft">
        	<?php print render($page['navigationLeft']); ?>
        </div>
        <div id="navigationRight">
			<?php print render($page['navigationRight']); ?>
			</div>
        </div>
        <div class="clearfix"></div>
    </nav>
</div><!--end navigationWrapper-->



<div id="headerWrapper">
	<header id="header">
    	<div id="headerLeft">
        	<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/></a>
        </div>
        <div id="headerRight"><!--floats right -->
           	<?php print render($page['headerRight']); ?>
        </div>
        <div class="clearfix"></div>
    </header>
</div>


<section id="filterWrapper">
	<div id="filter">
		<?php print render($page['filter']); ?>
	</div>
</section>

<section id="bannerWrapper">
	<div id="banner">
		<?php print render($page['banner']); ?>
	</div>
</section>


<div id="contentWrapper">
	<div id="content">
        
        <section>
        <div class="sidedish">
        	<?php print render($page['sidedish1']); ?>
        </div>
        
        <div class="sidedish">
        	<?php print render($page['sidedish2']); ?>
        </div>
        
        <div class="sidedish">
        	<?php print render($page['sidedish3']); ?>
        </div>
        
        <div class="clearfix"></div>
    	</section>		
    
    </div>
</div>


<div id="footerWrapper">
    <footer id="footer">
    	<div id="footerLeft"><?php print render($page['footerLeft']); ?></div>
        <div id="footerCenter"><?php print render($page['footerCenter']); ?></div>
        <div id="footerRight"><?php print render($page['footerRight']); ?></div>
        <div class="clearfix"></div>
    </footer>
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
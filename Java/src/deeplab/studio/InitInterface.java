package deeplab.studio;

import deeplab.ojects.LocalizationHandler;
import deeplab.stages.CreateNetworkDialog;
import deeplab.util.Util;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.RadioMenuItem;
import javafx.scene.layout.BorderPane;


public class InitInterface extends Scene {
	
	
	// Menu Bar
	private MenuBar menuBar;
	// Menus
	private Menu fileMenu, createMenu, editMenu, sourceMenu, optionsMenu, runMenu, helpMenu;
	// Menu Items
	private MenuItem item_CreateNetwork, item_Import, item_Export, item_TrainingFile, item_TestFile, item_ValidationFile; // File Menu Items
	private RadioMenuItem menuItem_English, menuItem_German; // Options Menu Items
	
	
	public InitInterface( Parent root ) {
		super( root );
		Util.addStylesheet(this);
		BorderPane rootLayout = (BorderPane)root;
		LocalizationHandler localization = DeepLabStudio.getLocalization();
		
		menuBar = new MenuBar();
		
		// Menus
		fileMenu = new Menu( localization.getString( "initInterface.menu.file" ) );
		createMenu = new Menu( localization.getString( "initInterface.menu.create" ) );
		editMenu = new Menu( localization.getString( "initInterface.menu.edit" ) );
		sourceMenu = new Menu( localization.getString( "initInterface.menu.source" ) );
		optionsMenu = new Menu( localization.getString( "initInterface.menu.options" ) );
		runMenu = new Menu( localization.getString( "initInterface.menu.run" ) );
		helpMenu = new Menu( localization.getString( "initInterface.menu.help" ) );
		
		// File Menu Items
		item_CreateNetwork = new MenuItem( localization.getString( "initInterface.menu.item.createNetwork" ) );
		item_CreateNetwork.setOnAction( e -> newItemPressed() );
		item_Import = new MenuItem( localization.getString( "initInterface.menu.item.import" ) );
		item_Export = new MenuItem( localization.getString( "initInterface.menu.item.export" ) );
		item_TrainingFile = new MenuItem( localization.getString( "initInterface.menu.item.trainingFile" ) );
		item_TestFile = new MenuItem( localization.getString( "initInterface.menu.item.testFile" ) );
		item_ValidationFile = new MenuItem( localization.getString( "initInterface.menu.item.validationFile" ) );
		fileMenu.getItems().addAll( item_CreateNetwork,item_Import,item_Export,item_TrainingFile,item_TestFile,item_ValidationFile );
		
		// Create Menu Items
		
		// Edit Menu Items
		
		// Source Menu Items
		
		// Options Menu Items
		menuItem_English = new RadioMenuItem( "English" );
		menuItem_German = new RadioMenuItem( "German" );
		optionsMenu.getItems().addAll( menuItem_English,menuItem_German );
		
		// Run Menu Items
		
		// Help Menu Items
		
		
		menuBar.getMenus().addAll( fileMenu,createMenu,editMenu,sourceMenu,optionsMenu,runMenu,helpMenu );
		rootLayout.setTop( menuBar );
	}
	
	
	private void newItemPressed() {
		CreateNetworkDialog createNetworkDialog = new CreateNetworkDialog();
	}
	
	
}

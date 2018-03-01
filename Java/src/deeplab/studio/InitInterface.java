package deeplab.studio;

import deeplab.ojects.LocalizationHandler;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.RadioMenuItem;
import javafx.scene.layout.BorderPane;

import java.net.URISyntaxException;
import java.util.Properties;


public class InitInterface extends Scene {
	
	
	private MenuBar menuBar;
	private Menu fileMenu, createMenu, editMenu, sourceMenu, optionsMenu, runMenu, helpMenu;
	private MenuItem newItem, importItem, exportItem, trainingFileItem, testFileItem, validationFileItem; // File Menu Items
	
	private RadioMenuItem english, german; // Options Menu Items
	
	
	public InitInterface( Parent root ) {
		super( root );
		try {
			super.getStylesheets().add( InitInterface.class.getResource( "/css/default.css" ).toURI().toString() );
		} catch( URISyntaxException e ) {
			System.err.println( "Failed to load default stylesheet for scene InitInterface" );
			e.printStackTrace();
		}
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
		newItem = new MenuItem( localization.getString( "initInterface.menu.item.new" ) );
		importItem = new MenuItem( localization.getString( "initInterface.menu.item.import" ) );
		exportItem = new MenuItem( localization.getString( "initInterface.menu.item.export" ) );
		trainingFileItem = new MenuItem( localization.getString( "initInterface.menu.item.trainingFile" ) );
		testFileItem = new MenuItem( localization.getString( "initInterface.menu.item.testFile" ) );
		validationFileItem = new MenuItem( localization.getString( "initInterface.menu.item.validationFile" ) );
		fileMenu.getItems().addAll( newItem,importItem,exportItem,trainingFileItem,testFileItem,validationFileItem );
		
		// Create Menu Items
		
		// Edit Menu Items
		
		// Source Menu Items
		
		// Options Menu Items
		english = new RadioMenuItem( "English" );
		german = new RadioMenuItem( "German" );
		optionsMenu.getItems().addAll( english,german );
		
		// Run Menu Items
		
		// Help Menu Items
		
		
		menuBar.getMenus().addAll( fileMenu,createMenu,editMenu,sourceMenu,optionsMenu,runMenu,helpMenu );
		rootLayout.setTop( menuBar );
	}
	
	
}

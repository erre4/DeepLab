package deeplab.studio;

import deeplab.ojects.LocalizationHandler;
import deeplab.ojects.SettingsHandler;
import javafx.application.Application;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Properties;


public class DeepLabStudio extends Application {
	
	
	private static SettingsHandler settings;
	private static LocalizationHandler localization;
	
	
	public static void main( String[] args ) {
		settings = new SettingsHandler();
		settings.loadSettingsFrom( "settings.properties" );
		
		localization = new LocalizationHandler();
		localization.addLocalizationFile( "/localizations/en.txt","en" );
		localization.addLocalizationFile( "/localizations/de.txt","de" );
		localization.setLanguage( settings.getString( "language" ) );
		
		launch( args );
	}
	
	
	@Override
	public void start( Stage primaryStage ) {
		String windowTitle = localization.getString( "window.title" ) + " - v" + settings.getString( "version" );
		int windowWidth = settings.getInt( "window.width" );
		int windowHeight =  settings.getInt( "window.height" );
		int minWindowWidth = 800;
		int minWindowHeight = 600;
		
		primaryStage.setTitle( windowTitle );
		primaryStage.setWidth( windowWidth );
		primaryStage.setHeight( windowHeight );
		primaryStage.setMinWidth( minWindowWidth );
		primaryStage.setMinHeight( minWindowHeight );
		
		primaryStage.setScene( new InitInterface( new BorderPane() ) );
		
		primaryStage.show();
	}
	
	
	public static LocalizationHandler getLocalization() {
		return localization;
	}
	
	
}

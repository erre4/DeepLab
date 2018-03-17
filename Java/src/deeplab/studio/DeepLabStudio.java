package deeplab.studio;

import deeplab.ojects.LocalizationHandler;
import deeplab.ojects.SettingsHandler;
import javafx.application.Application;
import javafx.scene.image.Image;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Properties;


public class DeepLabStudio extends Application {
	
	
	private static Stage primaryStage;
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
		primaryStage.getIcons().addAll( new Image( DeepLabStudio.class.getResourceAsStream( "/icon_512.png" ) ) );
		DeepLabStudio.primaryStage = primaryStage;
		
		primaryStage.setTitle( localization.getString( "window.title" ) + " - v" + settings.getString( "version" ) );
		primaryStage.setWidth( settings.getInt( "window.width" ) );
		primaryStage.setHeight( settings.getInt( "window.height" ) );
		primaryStage.setMinWidth( 800 );
		primaryStage.setMinHeight( 600 );
		
		primaryStage.setScene( new InitInterface( new BorderPane() ) );
		primaryStage.show();
	}
	
	
	public static Stage getPrimaryStage() {
		return primaryStage;
	}
	
	public static LocalizationHandler getLocalization() {
		return localization;
	}
	
	
}

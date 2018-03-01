package deeplab.ojects;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Properties;


public class LocalizationHandler {
	
	
	private HashMap<String,Properties> localizationFiles;
	private Properties currentLocalizationFile;
	
	
	public LocalizationHandler() {
		localizationFiles = new HashMap<>();
	}
	
	
	public void addLocalizationFile( String source,String languageCode ) {
		Properties properties = new Properties();
		try {
			properties.load( LocalizationHandler.class.getResourceAsStream( source ) );
		} catch( IOException e ) {
			System.err.println( "Error loading localization file from " + source );
			e.printStackTrace();
		}
		localizationFiles.put( languageCode,properties );
	}
	
	public void setLanguage( String languageCode ) {
		if( !localizationFiles.containsKey( languageCode ) )
			throw new IllegalArgumentException( "There is not localization file with the language code " + languageCode );
		currentLocalizationFile = localizationFiles.get( languageCode );
	}
	
	
	public String getString(String key) {
		return currentLocalizationFile.getProperty( key );
	}
	
	
}

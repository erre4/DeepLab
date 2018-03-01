package deeplab.ojects;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;


public class SettingsHandler {
	
	
	private Properties properties;
	
	private String stringDefault;
	private int intDefault;
	
	
	public SettingsHandler() {
		properties = new Properties();
		stringDefault = "?";
		intDefault = 0;
	}
	
	
	public void loadSettingsFrom( String source ) {
		try {
			properties.load( new FileInputStream( source ) );
		} catch( IOException e ) {
			System.err.println( "Error loading settings file from " + source );
			e.printStackTrace();
		}
	}
	
	public void saveSettingsTo( String target ) {
		try {
			properties.store( new FileOutputStream( target ),"" );
		} catch( IOException e ) {
			System.err.println( "Error saving setting file to " + target );
			e.printStackTrace();
		}
	}
	
	
	public String getString( String key ) {
		return properties.getProperty( key,stringDefault );
	}
	
	public void setString( String key,String value ) {
		properties.setProperty( key,value );
	}
	
	public int getInt( String key ) {
		return Integer.parseInt( properties.getProperty( key,"" + intDefault ) );
	}
	
	public void setInt( String key,int value ) {
		properties.setProperty( key,"" + value );
	}
	
	
}

package deeplab.util;


import deeplab.studio.InitInterface;
import javafx.scene.Scene;

import java.net.URISyntaxException;


public class Util {
	
	
	public static void addStylesheet(Scene scene) {
		try {
			scene.getStylesheets().add( InitInterface.class.getResource( "/css/default.css" ).toURI().toString() );
		} catch( URISyntaxException e ) {
			System.err.println( "Failed to load default stylesheet for scene InitInterface" );
			e.printStackTrace();
		}
	}
	
	
}

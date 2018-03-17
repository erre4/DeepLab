package deeplab.ojects;


import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.TextField;


public class NumberField extends TextField {
	
	
	public NumberField() {
		super();
		super.textProperty().addListener( new ChangeListener<String>() {
			@Override
			public void changed( ObservableValue<? extends String> observable,String oldValue,String newValue ) {
				if(!newValue.matches( "\\d*" ))
					setText( oldValue );
			}
		} );
	}
	
	
	public int getValue() {
		return Integer.parseInt( super.getText() );
	}
	
	
}

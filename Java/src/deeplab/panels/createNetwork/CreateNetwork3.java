package deeplab.panels.createNetwork;


import deeplab.stages.CreateNetworkDialog;
import deeplab.util.Util;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Orientation;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;

import java.awt.*;


public class CreateNetwork3 extends Scene {
	
	
	public static final int PANEL_TYPE_FULLY_CONNECTED = 0x0;
	public static final int PANEL_TYPE_CONVOLUTIONAL = 0x1;
	public static final int PANEL_TYPE_RESIDUAL = 0x2;
	
	// Component Lists
	private int[] panelTypes;
	private Label[] labels_Type,labels_InputNeurons,labels_OutputNeurons;
	private Label[] labels_InputNeuronChannels,labels_InputNeuronRows,labels_InputNeuronColumns;
	private Spinner<Integer>[] spinners_InputNeuronChannels,spinners_InputNeuronRows,spinners_InputNeuronColumns;
	private Label[] labels_OutputNeuronChannels,labels_OutputNeuronRows,labels_OutputNeuronColumns;
	private Spinner<Integer>[] spinners_OutputNeuronChannels,spinners_OutputNeuronRows,spinners_OutputNeuronColumns;
	private Label[] labels_SizeOfKernel,labels_Stride,labels_FeatureMaps,labels_Pooling;
	private Spinner<Integer>[] spinners_SizeOfKernelRows,spinners_SizeOfKernelColumns,spinners_Stride,spinners_FeatureMaps,spinners_Pooling;
	private Label[] labels_SizeOfKernelRows,labels_SizeOfKernelColumns;
	// Buttons
	private Button button_Back, button_Finish;
	
	private int previousPanelType;
	
	
	public CreateNetwork3( VBox root,int hiddenLayers,CreateNetworkDialog createNetworkDialog ) {
		super( root );
		Util.addStylesheet(this);
		root.setPadding( new Insets( 5 ) );
		root.setSpacing( 10 );
		
		
		// Component Lists Initialization
		panelTypes = new int[hiddenLayers];
		labels_Type = new Label[hiddenLayers];
		labels_InputNeurons = new Label[hiddenLayers];
		labels_OutputNeurons = new Label[hiddenLayers];
		labels_InputNeuronChannels = new Label[hiddenLayers];
		labels_InputNeuronRows = new Label[hiddenLayers];
		labels_InputNeuronColumns = new Label[hiddenLayers];
		spinners_InputNeuronChannels = new Spinner[hiddenLayers];
		spinners_InputNeuronRows = new Spinner[hiddenLayers];
		spinners_InputNeuronColumns = new Spinner[hiddenLayers];
		labels_OutputNeuronChannels = new Label[hiddenLayers];
		labels_OutputNeuronRows = new Label[hiddenLayers];
		labels_OutputNeuronColumns = new Label[hiddenLayers];
		spinners_OutputNeuronChannels = new Spinner[hiddenLayers];
		spinners_OutputNeuronRows = new Spinner[hiddenLayers];
		spinners_OutputNeuronColumns = new Spinner[hiddenLayers];
		labels_SizeOfKernel = new Label[hiddenLayers];
		labels_Stride = new Label[hiddenLayers];
		labels_FeatureMaps = new Label[hiddenLayers];
		labels_Pooling = new Label[hiddenLayers];
		spinners_SizeOfKernelRows = new Spinner[hiddenLayers];
		spinners_SizeOfKernelColumns = new Spinner[hiddenLayers];
		spinners_Stride = new Spinner[hiddenLayers];
		spinners_FeatureMaps = new Spinner[hiddenLayers];
		spinners_Pooling = new Spinner[hiddenLayers];
		labels_SizeOfKernelRows = new Label[hiddenLayers];
		labels_SizeOfKernelColumns = new Label[hiddenLayers];
		
		
		// Create Components
		VBox layout_Components = new VBox( 5 );
		for( int i = 0; i < createNetworkDialog.panel_CreateNetwork1.getHiddenLayersValue(); i++ ) {
			final int run = i;
			
			VBox layout_OneComponent = new VBox( 10 );
			layout_OneComponent.setAlignment( Pos.BASELINE_CENTER );
			HBox layout_OneComponent_inner = new HBox( 5 );
			
			if(createNetworkDialog.panel_CreateNetwork2.getToggleGroups()[i].getSelectedToggle().getUserData().equals( "fully connected" )) {
				previousPanelType = PANEL_TYPE_FULLY_CONNECTED;
				panelTypes[i]=PANEL_TYPE_FULLY_CONNECTED;
				
				labels_Type[i] = new Label( "Hidden Layer No "+i+" - Fully Connected" );
				labels_Type[i].setFont( new Font( 14 ) );
				
				
				// INPUT NEURONS
				VBox layout_InputNeurons = new VBox( 5 );
				layout_InputNeurons.setAlignment( Pos.BASELINE_CENTER );
				labels_InputNeurons[i] = new Label( "Number of Input Neurons" );
				HBox layout_InputNeurons_components = new HBox( 5 );
				// Channels for Input Neurons
				VBox layout_InputNeurons_components_Channels = new VBox( 5 );
				layout_InputNeurons_components_Channels.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronChannels[i] = new Spinner(1,99,1);
				spinners_InputNeuronChannels[i].setEditable( true );
				spinners_InputNeuronChannels[i].setPrefWidth( 55 );
				labels_InputNeuronChannels[i] = new Label( "Channels" );
				labels_InputNeuronChannels[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Channels.getChildren().addAll( spinners_InputNeuronChannels[i],labels_InputNeuronChannels[i] );
				// Rows for Input Neurons
				VBox layout_InputNeurons_components_Rows = new VBox( 5 );
				layout_InputNeurons_components_Rows.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronRows[i] = new Spinner<>( 1,99,1 );
				spinners_InputNeuronRows[i].setEditable( true );
				spinners_InputNeuronRows[i].setPrefWidth( 55 );
				labels_InputNeuronRows[i] = new Label( "Rows" );
				labels_InputNeuronRows[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Rows.getChildren().addAll( spinners_InputNeuronRows[i],labels_InputNeuronRows[i] );
				// Columns for Input Neurons
				VBox layout_InputNeurons_components_Columns = new VBox( 5 );
				layout_InputNeurons_components_Columns.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronColumns[i] = new Spinner<>( 1,99,1 );
				spinners_InputNeuronColumns[i].setEditable( true );
				spinners_InputNeuronColumns[i].setPrefWidth( 55 );
				labels_InputNeuronColumns[i] = new Label( "Columns" );
				labels_InputNeuronColumns[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Columns.getChildren().addAll( spinners_InputNeuronColumns[i],labels_InputNeuronColumns[i] );
				// Add everything together
				layout_InputNeurons_components.getChildren().addAll( layout_InputNeurons_components_Channels,layout_InputNeurons_components_Rows,layout_InputNeurons_components_Columns );
				layout_InputNeurons.getChildren().addAll( labels_InputNeurons[i],layout_InputNeurons_components );
				
				
				// OUTPUT NEURONS
				VBox layout_OutputNeurons = new VBox( 5 );
				layout_OutputNeurons.setAlignment( Pos.BASELINE_CENTER );
				labels_OutputNeurons[i] = new Label( "Number of Output Neurons" );
				HBox layout_OutputNeurons_components = new HBox( 5 );
				// Channels for Output Neurons
				VBox layout_OutputNeurons_components_Channels = new VBox( 5 );
				layout_OutputNeurons_components_Channels.setAlignment( Pos.BASELINE_CENTER );
				spinners_OutputNeuronChannels[i] = new Spinner<>( 1,99,1 );
				spinners_OutputNeuronChannels[i].setEditable( true );
				spinners_OutputNeuronChannels[i].setPrefWidth( 55 );
				spinners_OutputNeuronChannels[i].valueProperty().addListener( e->{
					if(panelTypes[run+1]!=PANEL_TYPE_FULLY_CONNECTED) {
						spinners_InputNeuronChannels[run+1].getValueFactory().setValue( spinners_OutputNeuronChannels[run].getValue() );
					}
				} );
				labels_OutputNeuronChannels[i] = new Label( "Channels" );
				labels_OutputNeuronChannels[i].setFont( new Font( 11 ) );
				layout_OutputNeurons_components_Channels.getChildren().addAll( spinners_OutputNeuronChannels[i],labels_OutputNeuronChannels[i] );
				// Rows for Output Neurons
				VBox layout_OutputNeurons_components_Rows = new VBox( 5 );
				layout_OutputNeurons_components_Rows.setAlignment( Pos.BASELINE_CENTER );
				spinners_OutputNeuronRows[i] = new Spinner<>( 1,99,1 );
				spinners_OutputNeuronRows[i].setEditable( true );
				spinners_OutputNeuronRows[i].setPrefWidth( 55 );
				spinners_OutputNeuronRows[i].valueProperty().addListener( e->{
					if(panelTypes[run+1]!=PANEL_TYPE_FULLY_CONNECTED) {
						spinners_InputNeuronRows[run+1].getValueFactory().setValue( spinners_OutputNeuronRows[run].getValue() );
					}
				} );
				labels_OutputNeuronRows[i] = new Label( "Rows" );
				labels_OutputNeuronRows[i].setFont( new Font( 11 ) );
				layout_OutputNeurons_components_Rows.getChildren().addAll( spinners_OutputNeuronRows[i],labels_OutputNeuronRows[i] );
				// Columns for Output Neurons
				VBox layout_OutputNeurons_components_Columns = new VBox( 5 );
				layout_OutputNeurons_components_Columns.setAlignment( Pos.BASELINE_CENTER );
				spinners_OutputNeuronColumns[i] = new Spinner<>( 1,99,1 );
				spinners_OutputNeuronColumns[i].setEditable( true );
				spinners_OutputNeuronColumns[i].setPrefWidth( 55 );
				spinners_OutputNeuronColumns[i].valueProperty().addListener( e->{
					if(panelTypes[run+1]!=PANEL_TYPE_FULLY_CONNECTED) {
						spinners_InputNeuronColumns[run+1].getValueFactory().setValue( spinners_OutputNeuronColumns[run].getValue() );
					}
				} );
				labels_OutputNeuronColumns[i] = new Label( "Columns" );
				labels_OutputNeuronColumns[i].setFont( new Font( 11 ) );
				layout_OutputNeurons_components_Columns.getChildren().addAll( spinners_OutputNeuronColumns[i],labels_OutputNeuronColumns[i] );
				// Add everything together
				layout_OutputNeurons_components.getChildren().addAll( layout_OutputNeurons_components_Channels,layout_OutputNeurons_components_Rows,layout_OutputNeurons_components_Columns );
				layout_OutputNeurons.getChildren().addAll( labels_OutputNeurons[i],layout_OutputNeurons_components );
				
				
				// CHECK IF FIRST FULLY CONNECTED PANEL
				if(i==0) {
					spinners_InputNeuronChannels[i].getValueFactory().setValue( createNetworkDialog.panel_CreateNetwork1.getChannelsValue());
					spinners_InputNeuronRows[i].getValueFactory().setValue( createNetworkDialog.panel_CreateNetwork1.getRowsValue());
					spinners_InputNeuronColumns[i].getValueFactory().setValue( createNetworkDialog.panel_CreateNetwork1.getColumnsValue());
				}
				
				
				
				Separator separator = new Separator( Orientation.VERTICAL );
				layout_OneComponent_inner.getChildren().addAll( layout_InputNeurons,separator,layout_OutputNeurons );
			} else if(createNetworkDialog.panel_CreateNetwork2.getToggleGroups()[i].getSelectedToggle().getUserData().equals( "convolutional" )) {
				previousPanelType = PANEL_TYPE_CONVOLUTIONAL;
				panelTypes[i]=PANEL_TYPE_CONVOLUTIONAL;
				
				labels_Type[i] = new Label( "Hidden Layer No "+i+" - Convolutional" );
				labels_Type[i].setFont( new Font( 14 ) );
				
				
				// INPUT NEURONS
				VBox layout_InputNeurons = new VBox( 5 );
				layout_InputNeurons.setAlignment( Pos.BASELINE_CENTER );
				labels_InputNeurons[i] = new Label( "Number of Input Neurons" );
				HBox layout_InputNeurons_components = new HBox( 5 );
				// Channels for Input Neurons
				VBox layout_InputNeurons_components_Channels = new VBox( 5 );
				layout_InputNeurons_components_Channels.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronChannels[i] = new Spinner(1,99,1);
				spinners_InputNeuronChannels[i].setEditable( true );
				spinners_InputNeuronChannels[i].setPrefWidth( 55 );
				spinners_InputNeuronChannels[i].setDisable( true );
				labels_InputNeuronChannels[i] = new Label( "Channels" );
				labels_InputNeuronChannels[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Channels.getChildren().addAll( spinners_InputNeuronChannels[i],labels_InputNeuronChannels[i] );
				// Rows for Input Neurons
				VBox layout_InputNeurons_components_Rows = new VBox( 5 );
				layout_InputNeurons_components_Rows.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronRows[i] = new Spinner<>( 1,99,1 );
				spinners_InputNeuronRows[i].setEditable( true );
				spinners_InputNeuronRows[i].setPrefWidth( 55 );
				spinners_InputNeuronRows[i].setDisable( true );
				labels_InputNeuronRows[i] = new Label( "Rows" );
				labels_InputNeuronRows[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Rows.getChildren().addAll( spinners_InputNeuronRows[i],labels_InputNeuronRows[i] );
				// Columns for Input Neurons
				VBox layout_InputNeurons_components_Columns = new VBox( 5 );
				layout_InputNeurons_components_Columns.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronColumns[i] = new Spinner<>( 1,99,1 );
				spinners_InputNeuronColumns[i].setEditable( true );
				spinners_InputNeuronColumns[i].setPrefWidth( 55 );
				spinners_InputNeuronColumns[i].setDisable( true );
				labels_InputNeuronColumns[i] = new Label( "Columns" );
				labels_InputNeuronColumns[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Columns.getChildren().addAll( spinners_InputNeuronColumns[i],labels_InputNeuronColumns[i] );
				// Add everything together
				layout_InputNeurons_components.getChildren().addAll( layout_InputNeurons_components_Channels,layout_InputNeurons_components_Rows,layout_InputNeurons_components_Columns );
				layout_InputNeurons.getChildren().addAll( labels_InputNeurons[i],layout_InputNeurons_components );
				
				
				// SIZE OF KERNEL
				VBox layout_SizeOfKernel = new VBox( 5 );
				layout_SizeOfKernel.setAlignment( Pos.BASELINE_CENTER );
				labels_SizeOfKernel[i] = new Label( "Size of Kernel" );
				HBox layout_SizeOfKernel_components = new HBox( 5 );
				// Rows for Size of Kernel
				VBox layout_SizeOfKernel_components_Rows = new VBox( 5 );
				layout_SizeOfKernel_components_Rows.setAlignment( Pos.BASELINE_CENTER );
				spinners_SizeOfKernelRows[i] = new Spinner<>( 1,99,1 );
				spinners_SizeOfKernelRows[i].setEditable( true );
				spinners_SizeOfKernelRows[i].setPrefWidth( 55 );
				labels_SizeOfKernelRows[i] = new Label( "Rows" );
				labels_SizeOfKernelRows[i].setFont( new Font( 11 ) );
				layout_SizeOfKernel_components_Rows.getChildren().addAll( spinners_SizeOfKernelRows[i],labels_SizeOfKernelRows[i] );
				// Columns for Size of Kernel
				VBox layout_SizeOfKernel_components_Columns = new VBox( 5 );
				layout_SizeOfKernel_components_Columns.setAlignment( Pos.BASELINE_CENTER );
				spinners_SizeOfKernelColumns[i] = new Spinner<>( 1,99,1 );
				spinners_SizeOfKernelColumns[i].setEditable( true );
				spinners_SizeOfKernelColumns[i].setPrefWidth( 55 );
				labels_SizeOfKernelColumns[i] = new Label( "Columns" );
				labels_SizeOfKernelColumns[i].setFont( new Font( 11 ) );
				layout_SizeOfKernel_components_Columns.getChildren().addAll( spinners_SizeOfKernelColumns[i],labels_SizeOfKernelColumns[i] );
				// Add everything together
				layout_SizeOfKernel_components.getChildren().addAll( layout_SizeOfKernel_components_Rows,layout_SizeOfKernel_components_Columns );
				layout_SizeOfKernel.getChildren().addAll( labels_SizeOfKernel[i],layout_SizeOfKernel_components );
				
				
				// STRIDE
				VBox layout_Stride = new VBox( 5 );
				layout_Stride.setAlignment( Pos.BASELINE_CENTER );
				labels_Stride[i] = new Label( "Stride" );
				spinners_Stride[i] = new Spinner<>( 1,99,1 );
				spinners_Stride[i].setEditable( true );
				spinners_Stride[i].setPrefWidth( 55 );
				layout_Stride.getChildren().addAll( labels_Stride[i],spinners_Stride[i] );
				
				
				// FEATURE MAPS
				VBox layout_FeatureMaps = new VBox( 5 );
				layout_FeatureMaps.setAlignment( Pos.BASELINE_CENTER );
				labels_FeatureMaps[i] = new Label( "Feature Maps" );
				spinners_FeatureMaps[i] = new Spinner<>( 1,99,1 );
				spinners_FeatureMaps[i].setEditable( true );
				spinners_FeatureMaps[i].setPrefWidth( 55 );
				layout_FeatureMaps.getChildren().addAll( labels_FeatureMaps[i],spinners_FeatureMaps[i] );
				
				
				// POOLING
				VBox layout_Pooling = new VBox( 5 );
				layout_Pooling.setAlignment( Pos.BASELINE_CENTER );
				labels_Pooling[i] = new Label( "Pooling" );
				spinners_Pooling[i] = new Spinner<>( 1,99,1 );
				spinners_Pooling[i].setEditable( true );
				spinners_Pooling[i].setPrefWidth( 55 );
				spinners_Pooling[i].setDisable( !createNetworkDialog.panel_CreateNetwork2.getCheckBoxes_Pooling()[i].isSelected() );
				layout_Pooling.getChildren().addAll( labels_Pooling[i],spinners_Pooling[i] );
				
				
				Separator separator1 = new Separator( Orientation.VERTICAL );
				Separator separator2 = new Separator( Orientation.VERTICAL );
				layout_OneComponent_inner.getChildren().addAll( layout_InputNeurons,separator1,layout_SizeOfKernel,separator2,layout_Stride,layout_FeatureMaps,layout_Pooling );
			} else if(createNetworkDialog.panel_CreateNetwork2.getToggleGroups()[i].getSelectedToggle().getUserData().equals( "residual" )) {
				previousPanelType = PANEL_TYPE_RESIDUAL;
				panelTypes[i]=PANEL_TYPE_RESIDUAL;
				
				labels_Type[i] = new Label( "Hidden Layer No "+i+" - Residual" );
				labels_Type[i].setFont( new Font( 14 ) );
				
				
				// INPUT NEURONS
				VBox layout_InputNeurons = new VBox( 5 );
				layout_InputNeurons.setAlignment( Pos.BASELINE_CENTER );
				labels_InputNeurons[i] = new Label( "Number of Input Neurons" );
				HBox layout_InputNeurons_components = new HBox( 5 );
				// Channels for Input Neurons
				VBox layout_InputNeurons_components_Channels = new VBox( 5 );
				layout_InputNeurons_components_Channels.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronChannels[i] = new Spinner(1,99,1);
				spinners_InputNeuronChannels[i].setEditable( true );
				spinners_InputNeuronChannels[i].setPrefWidth( 55 );
				spinners_InputNeuronChannels[i].setDisable( true );
				labels_InputNeuronChannels[i] = new Label( "Channels" );
				labels_InputNeuronChannels[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Channels.getChildren().addAll( spinners_InputNeuronChannels[i],labels_InputNeuronChannels[i] );
				// Rows for Input Neurons
				VBox layout_InputNeurons_components_Rows = new VBox( 5 );
				layout_InputNeurons_components_Rows.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronRows[i] = new Spinner<>( 1,99,1 );
				spinners_InputNeuronRows[i].setEditable( true );
				spinners_InputNeuronRows[i].setPrefWidth( 55 );
				spinners_InputNeuronRows[i].setDisable( true );
				labels_InputNeuronRows[i] = new Label( "Rows" );
				labels_InputNeuronRows[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Rows.getChildren().addAll( spinners_InputNeuronRows[i],labels_InputNeuronRows[i] );
				// Columns for Input Neurons
				VBox layout_InputNeurons_components_Columns = new VBox( 5 );
				layout_InputNeurons_components_Columns.setAlignment( Pos.BASELINE_CENTER );
				spinners_InputNeuronColumns[i] = new Spinner<>( 1,99,1 );
				spinners_InputNeuronColumns[i].setEditable( true );
				spinners_InputNeuronColumns[i].setPrefWidth( 55 );
				spinners_InputNeuronColumns[i].setDisable( true );
				labels_InputNeuronColumns[i] = new Label( "Columns" );
				labels_InputNeuronColumns[i].setFont( new Font( 11 ) );
				layout_InputNeurons_components_Columns.getChildren().addAll( spinners_InputNeuronColumns[i],labels_InputNeuronColumns[i] );
				// Add everything together
				layout_InputNeurons_components.getChildren().addAll( layout_InputNeurons_components_Channels,layout_InputNeurons_components_Rows,layout_InputNeurons_components_Columns );
				layout_InputNeurons.getChildren().addAll( labels_InputNeurons[i],layout_InputNeurons_components );
				
				
				// OUTPUT NEURONS
				VBox layout_OutputNeurons = new VBox( 5 );
				layout_OutputNeurons.setAlignment( Pos.BASELINE_CENTER );
				labels_OutputNeurons[i] = new Label( "Number of Output Neurons" );
				HBox layout_OutputNeurons_components = new HBox( 5 );
				// Channels for Output Neurons
				VBox layout_OutputNeurons_components_Channels = new VBox( 5 );
				layout_OutputNeurons_components_Channels.setAlignment( Pos.BASELINE_CENTER );
				spinners_OutputNeuronChannels[i] = new Spinner<>( 1,99,1 );
				spinners_OutputNeuronChannels[i].setEditable( true );
				spinners_OutputNeuronChannels[i].setPrefWidth( 55 );
				spinners_OutputNeuronChannels[i].setDisable( true );
				labels_OutputNeuronChannels[i] = new Label( "Channels" );
				labels_OutputNeuronChannels[i].setFont( new Font( 11 ) );
				layout_OutputNeurons_components_Channels.getChildren().addAll( spinners_OutputNeuronChannels[i],labels_OutputNeuronChannels[i] );
				// Rows for Output Neurons
				VBox layout_OutputNeurons_components_Rows = new VBox( 5 );
				layout_OutputNeurons_components_Rows.setAlignment( Pos.BASELINE_CENTER );
				spinners_OutputNeuronRows[i] = new Spinner<>( 1,99,1 );
				spinners_OutputNeuronRows[i].setEditable( true );
				spinners_OutputNeuronRows[i].setPrefWidth( 55 );
				spinners_OutputNeuronRows[i].setDisable( true );
				labels_OutputNeuronRows[i] = new Label( "Rows" );
				labels_OutputNeuronRows[i].setFont( new Font( 11 ) );
				layout_OutputNeurons_components_Rows.getChildren().addAll( spinners_OutputNeuronRows[i],labels_OutputNeuronRows[i] );
				// Columns for Output Neurons
				VBox layout_OutputNeurons_components_Columns = new VBox( 5 );
				layout_OutputNeurons_components_Columns.setAlignment( Pos.BASELINE_CENTER );
				spinners_OutputNeuronColumns[i] = new Spinner<>( 1,99,1 );
				spinners_OutputNeuronColumns[i].setEditable( true );
				spinners_OutputNeuronColumns[i].setPrefWidth( 55 );
				spinners_OutputNeuronColumns[i].setDisable( true );
				labels_OutputNeuronColumns[i] = new Label( "Columns" );
				labels_OutputNeuronColumns[i].setFont( new Font( 11 ) );
				layout_OutputNeurons_components_Columns.getChildren().addAll( spinners_OutputNeuronColumns[i],labels_OutputNeuronColumns[i] );
				// Add everything together
				layout_OutputNeurons_components.getChildren().addAll( layout_OutputNeurons_components_Channels,layout_OutputNeurons_components_Rows,layout_OutputNeurons_components_Columns );
				layout_OutputNeurons.getChildren().addAll( labels_OutputNeurons[i],layout_OutputNeurons_components );
				
				
				Separator separator = new Separator( Orientation.VERTICAL );
				layout_OneComponent_inner.getChildren().addAll( layout_InputNeurons,separator,layout_OutputNeurons );
			}
			
			layout_OneComponent.getChildren().addAll( labels_Type[i],layout_OneComponent_inner );
			
			
			Separator separator = new Separator(  );
			layout_Components.getChildren().addAll( layout_OneComponent,separator );
		}
		
		
		// Buttons
		HBox layout_Buttons = new HBox( 5 );
		layout_Buttons.setAlignment( Pos.BASELINE_RIGHT );
		button_Back = new Button( "Back" );
		button_Finish = new Button( "Next" );
		layout_Buttons.getChildren().addAll( button_Back,button_Finish );
		
		
		root.getChildren().addAll( layout_Components,layout_Buttons );
	}
	
	
	public void addButtonBackListener( EventHandler eventHandler ) {
		button_Back.setOnAction( e -> eventHandler.handle( e ) );
	}
	
	public void addButtonFinishListener( EventHandler eventHandler ) {
		button_Finish.setOnAction( e -> eventHandler.handle( e ) );
	}
	
	
}

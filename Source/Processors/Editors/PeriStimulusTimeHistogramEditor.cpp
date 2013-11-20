/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "PeriStimulusTimeHistogramEditor.h"
#include "../../UI/EditorViewport.h"
#include "../TrialCircularBuffer.h"
#include <stdio.h>

//FileSearchPathListComponent::paintListBoxItem	
PeriStimulusTimeHistogramEditor::PeriStimulusTimeHistogramEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors=true)
    : VisualizerEditor(parentNode, useDefaultParameterEditors) ,periStimulusTimeHistogramCanvas(nullptr)
{
	tabText = "PSTH";
    desiredWidth = 300;

	  visibleConditions = new ComboBox("Conditions");

    visibleConditions->setEditableText(false);
    visibleConditions->setJustificationType(Justification::centredLeft);
    visibleConditions->addListener(this);
    visibleConditions->setBounds(100,30,110,20);
    addAndMakeVisible(visibleConditions);

	condlabel = new Label("Conditions", "Conditions");
    condlabel->setBounds(10,30,100,20);
    condlabel->setFont(Font("Default", 15, Font::plain));
    condlabel->setColour(Label::textColourId, Colours::white);
    //condlabel->setColour(Label::backgroundColourId, Colours::grey);
    condlabel->setEditable(false);
    addAndMakeVisible(condlabel);
	
	autoRescale = new ToggleButton("Auto Rescale");//, Font("Small Text", 13, Font::plain));
    autoRescale->setBounds(35, 95, 130, 18);
    autoRescale->addListener(this);
	autoRescale->setToggleState(true,false);
    autoRescale->setClickingTogglesState(true);
    addAndMakeVisible(autoRescale);

	smoothPSTH = new ToggleButton("Smooth PSTH");//, Font("Small Text", 13, Font::plain));
    smoothPSTH->setBounds(135, 95, 130, 18);
    smoothPSTH->addListener(this);
	smoothPSTH->setToggleState(true,false);
    smoothPSTH->setClickingTogglesState(true);
    addAndMakeVisible(smoothPSTH);


	lfp = new ToggleButton("LFP");//, Font("Small Text", 13, Font::plain));
    lfp->setBounds(35, 55, 130, 18);
    lfp->addListener(this);
	lfp->setToggleState(true,false);
    lfp->setClickingTogglesState(true);
    addAndMakeVisible(lfp);

	spikes = new ToggleButton("Units");//, Font("Small Text", 13, Font::plain));
    spikes->setBounds(135, 55, 130, 18);
    spikes->addListener(this);
	spikes->setToggleState(true,false);
    spikes->setClickingTogglesState(true);
    addAndMakeVisible(spikes);



	smoothMS = new Label("Smooth MS", "10");
    smoothMS->setBounds(245,95,40,18);
    smoothMS->setFont(Font("Default", 15, Font::plain));
    smoothMS->setColour(Label::textColourId, Colours::white);
    smoothMS->setColour(Label::backgroundColourId, Colours::grey);
    smoothMS->setEditable(true);
    smoothMS->addListener(this);
    addAndMakeVisible(smoothMS);



   
}

void PeriStimulusTimeHistogramEditor::updateCondition(std::vector<Condition> conditions)
{
	visibleConditions->clear();
	
    for (int i = 0; i < conditions.size(); i++)
    {
        visibleConditions->addItem(conditions[i].name, i+1);
    }
}
void PeriStimulusTimeHistogramEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged) 
{
	
}


void PeriStimulusTimeHistogramEditor::buttonEvent(Button* button)
{
	VisualizerEditor::buttonEvent(button);
	if (periStimulusTimeHistogramCanvas == nullptr)
		return;

	if (button == lfp)
	{
		periStimulusTimeHistogramCanvas->setLFPvisibility(lfp->getToggleState());
	} else if (button == spikes)
	{
		periStimulusTimeHistogramCanvas->setSpikesVisibility(spikes->getToggleState());
	} else if (button == smoothPSTH)
	{
		periStimulusTimeHistogramCanvas->setSmoothPSTH(smoothPSTH->getToggleState());
	} else if (button == autoRescale)
	{
		periStimulusTimeHistogramCanvas->setAutoRescale(autoRescale->getToggleState());
	}

}


Visualizer* PeriStimulusTimeHistogramEditor::createNewCanvas()
{
    PeriStimulusTimeHistogramNode* processor = (PeriStimulusTimeHistogramNode*) getProcessor();
    periStimulusTimeHistogramCanvas = new PeriStimulusTimeHistogramCanvas(processor);
	return periStimulusTimeHistogramCanvas;
}

void PeriStimulusTimeHistogramEditor::updateCanvas()
{
	if (periStimulusTimeHistogramCanvas != nullptr) {
		periStimulusTimeHistogramCanvas->updateNeeded = true;
	}
}

PeriStimulusTimeHistogramEditor::~PeriStimulusTimeHistogramEditor()
{

  
}








/*
class ConditionsList : public ListBoxModel, public Component
{
public:
	ConditionsList();
    int getNumRows ();
	void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected);
	void paint(Graphics &g);
	void changed();

	ListBox listbox;
};

void ConditionsList::paint(Graphics &g)
{
	listbox.paint(g);
}

juce::ComboBox
void ConditionsList::changed()
{
    listbox.repaint();
    
}

int ConditionsList::getNumRows()
{
	return 5;
}
//	FileSearchPathListComponent::paintListBoxItem	

void ConditionsList::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    //if (rowIsSelected)
    //    g.fillAll (TextEditor::highlightColourId);

	g.setColour (juce::Colour(128,0,0));
    Font f (height * 0.7f);
    f.setHorizontalScale (0.9f);
    g.setFont (f);

	g.drawText ("Hello" + String(rowNumber),
                4, 0, width - 6, height,
                Justification::centredLeft, true);


}

ConditionsList::ConditionsList()
{
	listbox.setModel(this);
	
    listbox.setColour (ListBox::backgroundColourId, Colours::black.withAlpha (0.02f));
    listbox.setColour (ListBox::outlineColourId, Colours::black.withAlpha (0.1f));
    listbox.setOutlineThickness (1);

    listbox.setBounds(65,40,110,60);
    addAndMakeVisible (&listbox);

    //electrodeTypes->setSelectedId(1);
	//visibleConditions->set
    
}
*/


/********************************/
#ifndef MAX
#define MAX(x,y)((x)>(y))?(x):(y)
#endif 

#ifndef MIN
#define MIN(x,y)((x)<(y))?(x):(y)
#endif 


PeriStimulusTimeHistogramCanvas::PeriStimulusTimeHistogramCanvas(PeriStimulusTimeHistogramNode* n) :
	processor(n)
{


	showLFP = true;
	showSpikes = true;
	smoothPlots = true;
	autoRescale = true;
	viewport = new Viewport();
	psthDisplay = new PeriStimulusTimeHistogramDisplay(n, viewport, this);
	viewport->setViewedComponent(psthDisplay, false);
	viewport->setScrollBarsShown(true, true);

	addAndMakeVisible(viewport);
	
	update();
	
}


PeriStimulusTimeHistogramCanvas::~PeriStimulusTimeHistogramCanvas()
{

}

void PeriStimulusTimeHistogramCanvas::beginAnimation()
{
	startCallbacks();
}

void PeriStimulusTimeHistogramCanvas::buttonClicked(Button* button)
{

}

void PeriStimulusTimeHistogramCanvas::endAnimation()
{
	std::cout << "SpikeDisplayCanvas ending animation." << std::endl;

	stopCallbacks();
}


void PeriStimulusTimeHistogramCanvas::setLFPvisibility(bool visible)
{
	 showLFP = visible;
	 update();
}

void PeriStimulusTimeHistogramCanvas::setSpikesVisibility(bool visible)
{
	showSpikes = visible;
	update();
}

void PeriStimulusTimeHistogramCanvas::setSmoothPSTH(bool smooth)
{
	smoothPlots = smooth;
	update();
}

void PeriStimulusTimeHistogramCanvas::setAutoRescale(bool state)
{
	autoRescale = state;
	update();
}


void PeriStimulusTimeHistogramCanvas::refreshState()
{
	resized();
}

void PeriStimulusTimeHistogramCanvas::update()
{
	//std::cout << "Updating SpikeDisplayCanvas" << std::endl;
// clear all XY plots and create new ones...
	// delete all existing plots.
	// lock psth
	updateNeeded = false;
	for (int k=0; k < psthDisplay->psthPlots.size();k++)
	{
		delete psthDisplay->psthPlots[k];
	}
	psthDisplay->psthPlots.clear();
	if (processor->trialCircularBuffer == nullptr)
		return;

	processor->trialCircularBuffer->lockPSTH();
	numElectrodes = processor->trialCircularBuffer->electrodesPSTH.size();
	int maxUnitsPerElectrode = 0;
	int row = 0;

	for (int e=0;e<numElectrodes;e++) 
	{
		int offset = 0;
		bool plottedSomething = false;
		if (showLFP) {
			offset = processor->trialCircularBuffer->electrodesPSTH[e].channels.size();
			for (int u=0;u<processor->trialCircularBuffer->electrodesPSTH[e].channels.size();u++)
			{
				XYPlot *newplot = new XYPlot(false,processor->trialCircularBuffer,
					processor->trialCircularBuffer->electrodesPSTH[e].electrodeID,
					processor->trialCircularBuffer->electrodesPSTH[e].channels[u],
					u,row);
				psthDisplay->psthPlots.push_back(newplot);
				addAndMakeVisible(newplot);
				plottedSomething = true;
			}
			
		}
		
		if (showSpikes)
		{
			int numUnits = processor->trialCircularBuffer->electrodesPSTH[e].unitsPSTHs.size();
			maxUnitsPerElectrode = MAX(maxUnitsPerElectrode,numUnits );
			if (numUnits > 0) 
			{
				for (int u=0;u<numUnits;u++)
				{
					XYPlot *newplot = new XYPlot(true,processor->trialCircularBuffer,
						processor->trialCircularBuffer->electrodesPSTH[e].electrodeID,
						processor->trialCircularBuffer->electrodesPSTH[e].unitsPSTHs[u].unitID,
						offset+u,row);
					psthDisplay->psthPlots.push_back(newplot);
					addAndMakeVisible(newplot);
				}
				plottedSomething = true;
			}
		}
		if (plottedSomething)
			row++;			
	}
	if (maxUnitsPerElectrode == 0 && !showLFP) {
		// nothing to be drawn...
		processor->trialCircularBuffer->unlockPSTH();
		return;		
	}
    resized();

	heightPerElectrodePix = 200;
	widthPerUnit = 200;

	psthDisplay->resized();
	psthDisplay->repaint();
	processor->trialCircularBuffer->unlockPSTH();
}


void PeriStimulusTimeHistogramCanvas::resized()
{
    viewport->setBounds(0,0,getWidth(),getHeight()-20);
	int scrollBarThickness = viewport->getScrollBarThickness();


	int totalHeight = numElectrodes * heightPerElectrodePix;
	int totalWidth = maxUnitsPerElectrode * widthPerUnit;
    psthDisplay->setBounds(0,0,totalWidth-scrollBarThickness, totalHeight);

	
}

void PeriStimulusTimeHistogramCanvas::paint(Graphics& g)
{
	if (updateNeeded)
		update();
	g.fillAll(Colours::darkgrey);

}

void PeriStimulusTimeHistogramCanvas::refresh()
{
	repaint();
	psthDisplay->refresh();
}

/***********************************************/

PeriStimulusTimeHistogramDisplay::PeriStimulusTimeHistogramDisplay(PeriStimulusTimeHistogramNode* n, Viewport *p, PeriStimulusTimeHistogramCanvas*c) :
		processor(n), viewport(p), canvas(c)
{

	font = Font("Default", 15, Font::plain);
}

void PeriStimulusTimeHistogramDisplay::refresh()
{
	for (int k=0;k<psthPlots.size();k++)
	{
		psthPlots[k]->repaint();
	}

}


void PeriStimulusTimeHistogramDisplay::paint(Graphics &g)
{
	g.setColour(Colours::white);
	g.drawRect(0,0,getWidth(),getHeight());

	font = Font("Default", 15, Font::plain);
	
	g.setFont(font);

	g.drawText("Test",10,0,200,20,Justification::left,false);
}  

void PeriStimulusTimeHistogramDisplay::resized()
{
	int h = getHeight();
	int w = getWidth();

	
	// draw n by m grid
	for (int k=0;k<psthPlots.size();k++)
	{
		psthPlots[k]->setBounds(psthPlots[k]->row * canvas->widthPerUnit,
							    psthPlots[k]->col * canvas->heightPerElectrodePix,
								canvas->widthPerUnit,
								canvas->heightPerElectrodePix);

	}
}


/******************************************/
XYPlot::XYPlot(bool _spikePlot, TrialCircularBuffer *_tcb, int _electrodeID, int _unitID, int _row, int _col) :
	tcb(_tcb), electrodeID(_electrodeID), unitID(_unitID), row(_row), col(_col),spikePlot(_spikePlot)
{
	font = Font("Default", 15, Font::plain);
	guassianStandardDeviationMS = 5; // default smoothing
	buildSmoothKernel(guassianStandardDeviationMS); 
}

void XYPlot::mouseDown(const juce::MouseEvent& event)
{
	if (event.mods.isRightButtonDown())
	{

		tcb->lockPSTH();
		for (int electrodeIndex=0;electrodeIndex<	tcb->electrodesPSTH.size();electrodeIndex++)
		{
			if (tcb->electrodesPSTH[electrodeIndex].electrodeID == electrodeID)
			{
				if (spikePlot)
				{
					for (int unitIndex = 0; unitIndex < tcb->electrodesPSTH[electrodeIndex].unitsPSTHs.size();unitIndex++)
					{
						if (tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[unitIndex].unitID == unitID)
						{
							tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[unitIndex].clearStatistics();
							break;
						}
					}
				} else 
				{
					for (int Index = 0; Index < tcb->electrodesPSTH[electrodeIndex].channels.size();Index++)
					{
						if (tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[Index].channelID  == unitID)
						{
							tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[Index].clearStatistics();
							break;
						}
					}

				}
			}
		}
		tcb->unlockPSTH();
	}
}

void XYPlot::resized()
{

}



std::vector<int> XYPlot::histc(std::vector<float> xi, std::vector<float> x)
{
	std::vector<int> aiInd(xi.size());

	int i = 0;
	int j = 0;
	int N = x.size();
	while (i < xi.size()) 
	{
		if (xi[i] < x[j] || xi[i] > x[N-1])
		{
			aiInd[i] = -1;
			i++;
			continue;
		}
		if (j + 1 < N && xi[i] >= x[j] && xi[i] < x[j + 1])
		{
			aiInd[i] = j;
			i++;
			continue;
		}
		j++;
		if (j > N - 1)
			j = N - 1;
	}
	return aiInd;
}

std::vector<float> XYPlot::diff(std::vector<float> x)
{
	std::vector<float> d(x.size()-1);
	for (int k = 0; k < x.size() - 1; k++)
	{
		d[k] = x[k + 1] - x[k];
	}
	return d;
}


void XYPlot::interp1(std::vector<float> x, std::vector<float>y, std::vector<float> xi, std::vector<float> &yi, std::vector<bool> &valid)
{
	// linear interpolate
	int N = x.size();
	int M = xi.size();

	valid.resize(xi.size());
	yi.resize(xi.size());

	if (x.size()== 0)
		return;

	std::vector<int> ind = histc(xi, x);
	std::vector<float> h = diff(x);

	for (int i = 0; i < xi.size(); i++)
	{
		if (ind[i] < 0)
		{
			// invalid entry
			valid[i] = false;
			yi[i] = 0;
			continue;
		}
		valid[i] = true;

		double s = (xi[i] - x[ind[i]]) / h[ind[i]];
		yi[i] = y[ind[i]] + s * (y[ind[i] + 1] - y[ind[i]]);
	}

}

std::vector<float> XYPlot::smooth(std::vector<float> x)
{
	std::vector<float> smoothx;
	smoothx.resize(x.size());

	int numKernelBins = smoothKernel.size();
	int zeroIndex = (numKernelBins-1)/2;
	int numXbins = x.size();
	for (int k=0;k<numXbins;k++)
	{
		float response = 0;
		for (int j=-zeroIndex;j<zeroIndex;j++)
		{
			if (k+j >=0 && k+j < numXbins)
				response+=x[k+j] * smoothKernel[j+zeroIndex];
		}
		smoothx[k] = response;
	}
	return smoothx;
}

void XYPlot::buildSmoothKernel(float guassianStandardDeviationMS)
{
	// assume each bin correponds to one millisecond.
	// build the gaussian kernel
	int numKernelBins = 2*(int)(guassianStandardDeviationMS*3.5)+1; // +- 3.5 standard deviations.
	int zeroIndex = (numKernelBins-1)/2;
	smoothKernel.resize(numKernelBins); 
	float sumZ = 0;
	for (int k=0;k<numKernelBins;k++) 
	{
		float z = float(k-zeroIndex);
		smoothKernel[k] = exp(- (z*z)/(2*guassianStandardDeviationMS*guassianStandardDeviationMS));
		sumZ+=smoothKernel[k];
	}
	// normalize kernel
	for (int k=0;k<numKernelBins;k++) 
	{
		smoothKernel[k] /= sumZ;
	}
}


void XYPlot::paint(Graphics &g)
{
	int w = getWidth();
	int h = getHeight();
	// draw a bounding box of the plot.
	int x0;

	if (w >= 300) {
		font = Font("Default", 15, Font::plain);
		 x0 = 60;
	} else if (w >= 250)
	{
		font = Font("Default", 10, Font::plain);
		x0 = 50;
	} else 
	{
		font = Font("Default", 8, Font::plain);
		 x0 = 30;
	}


	int y0 = 30;

	int plotWidth  = getWidth()-1.5*x0;
	int plotHeight = getHeight()-2*y0;
	g.setColour(Colours::black);
	g.fillRect(x0,y0, plotWidth,plotHeight);
		
	g.setColour(Colours::white);
	g.drawRect(x0,y0, plotWidth,plotHeight);

	float xmin=0, xmax=0, ymax=0, ymin = 0;
	bool found = false;
	int electrodeIndex;
	int entryindex;
	tcb->lockPSTH();
	for (electrodeIndex=0;electrodeIndex<	tcb->electrodesPSTH.size();electrodeIndex++)
	{
		if (tcb->electrodesPSTH[electrodeIndex].electrodeID == electrodeID)
		{
			if (spikePlot)
			{
				for (entryindex = 0; entryindex < tcb->electrodesPSTH[electrodeIndex].unitsPSTHs.size();entryindex++)
				{
					if (tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].unitID == unitID)
					{
						found = true;
					// keep a fixed amount of pixels for axes labels
						g.setColour(juce::Colour(tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].colorRGB[0],
												 tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].colorRGB[1],
												  tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].colorRGB[2]));

						g.drawRect(0,0,w,h,2);

						tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].getRange(xmin, xmax, ymin,ymax);
						break;
					}
				}
			} else 
			{
				// lfp plot
				for (entryindex = 0; entryindex < tcb->electrodesPSTH[electrodeIndex].channelsPSTHs.size();entryindex++)
				{
					if (tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].channelID == unitID)
					{
						found = true;
					g.setColour(Colours::whitesmoke);
					g.drawRect(0,0,w,h);

						tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].getRange(xmin, xmax,ymin, ymax);
						break;
					}
				}
			}
		}
		if (found)
			break;
	}
	tcb->unlockPSTH();
	if (!found || xmin == xmax || ymax == 0)
		return; // nothing to draw.

	// determine tick position
	


	float axesRange[4] = {xmin,ymin, xmax, ymax}; // xmin,ymin, xmax, ymax
	float rangeX = (axesRange[2]-axesRange[0]);
	float rangeY = (axesRange[3]-axesRange[1]);
	int numXTicks = 5;
	int numYTicks = 5;

	// determine tick positions.
	std::vector<float> tickX,tickY;
	tickX.resize(numXTicks);
	tickY.resize(numYTicks);
	for (int k=0;k<numXTicks;k++)
	{
		tickX[k] = float(k)/(numXTicks-1) * rangeX +axesRange[0];
	}
	for (int k=0;k<numYTicks;k++)
	{
		tickY[k] = float(k)/(numYTicks-1) * rangeY +axesRange[1];
	}

	int tickHeight = 6;
	float tickThickness = 2;
	g.setColour(Colours::white);
	// plot the x axis
	g.drawLine(x0,h-y0,x0+plotWidth,h-y0, 1);
	// plot the y axis
	g.drawLine(x0,h-y0,x0,h-(y0+plotHeight),1);
	

		g.setFont(font);

	String axesName;
	if (spikePlot)
		axesName = String("Unit ")+String(tcb->electrodesPSTH[electrodeIndex].electrodeID)+":"+
			String(tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].unitID);
	else
		axesName = String("LFP ")+String(tcb->electrodesPSTH[electrodeIndex].electrodeID)+":"+
		String(tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].channelID);

	g.drawText(axesName,plotWidth/2,10,plotWidth/2,20,Justification::centred,false);
	
	float ticklabelWidth = float(plotWidth)/numXTicks;
	int tickLabelHeight = 20;
	// plot the tick marks and corresponding text.
	for (int k=0;k<numXTicks;k++)
	{
		// convert to screen coordinates.
		float tickloc = x0+(tickX[k]- axesRange[0]) / rangeX * plotWidth;
		g.drawLine(tickloc,h-y0,tickloc,h-(y0+tickHeight),tickThickness);
		String tickLabel(tickX[k],1);;
		if (k > 0)
			g.drawText(tickLabel,tickloc-ticklabelWidth/2,h-(y0),ticklabelWidth,tickLabelHeight,Justification::centred,false);
		else
			g.drawText(tickLabel,tickloc,h-(y0),ticklabelWidth,tickLabelHeight,Justification::left,false);

	}
	for (int k=1;k<numYTicks;k++)
	{
		// convert to screen coordinates.
		float tickloc = y0+(tickY[k]- axesRange[1]) / rangeY * plotHeight;
		g.drawLine(x0,h-tickloc,x0+tickHeight,h-tickloc, tickThickness);

		String tickLabel(tickY[k],1);;
		g.drawText(tickLabel,x0-ticklabelWidth-3,h-tickloc-tickLabelHeight/2,ticklabelWidth,tickLabelHeight,Justification::right,false);

	}
	
	// finally, draw the function....
	// first, generate the sample positions
	int subsample = 5; // subsample every 5 pixels
	int numSamplePoints = plotWidth/subsample;
	std::vector<float> samplePositions;
	samplePositions.resize(numSamplePoints);
	
	for (int k=0;k<numSamplePoints;k++)
	{
		samplePositions[k] = (float(k)/(numSamplePoints-1)) * rangeX + axesRange[0];
		// which corresponds to pixel location subsample*k
	}

	std::vector<float> f_xi,smooth_f_xi;


	tcb->lockPSTH();
	if (spikePlot)
	{
		for (int cond=0;cond<tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].conditionPSTHs.size();cond++)
		{

			std::vector<bool> valid;
			interp1(tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].conditionPSTHs[cond].binTime, 
				tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].conditionPSTHs[cond].avgResponse,
				samplePositions,  f_xi,  valid);

			smooth_f_xi = smooth(f_xi);
			// and finally.... plot!
			g.setColour(juce::Colour(tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].conditionPSTHs[cond].colorRGB[0],
				tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].conditionPSTHs[cond].colorRGB[1],
				tcb->electrodesPSTH[electrodeIndex].unitsPSTHs[entryindex].conditionPSTHs[cond].colorRGB[2]));

			for (int k=0;k<numSamplePoints-1;k++) 
			{
				// remap f_xi to pixels!
				float fx_pix = MIN(plotHeight, MAX(0,(smooth_f_xi[k]-axesRange[1])/rangeY * plotHeight));
				float fxp1_pix = MIN(plotHeight,MAX(0,(smooth_f_xi[k+1]-axesRange[1])/rangeY * plotHeight));
				if (valid[k] && valid[k+1])
					g.drawLine(x0+subsample*k, h-fx_pix-y0, x0+subsample*(k+1), h-fxp1_pix-y0);
			}

		}

	} else
	{
		// lfp plot
		for (int cond=0;cond<tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].conditionPSTHs.size();cond++)
		{

			std::vector<bool> valid;
			interp1(tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].conditionPSTHs[cond].binTime, 
				tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].conditionPSTHs[cond].avgResponse,
				samplePositions,  f_xi,  valid);

			// and finally.... plot!
			g.setColour(juce::Colour(tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].conditionPSTHs[cond].colorRGB[0],
				tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].conditionPSTHs[cond].colorRGB[1],
				tcb->electrodesPSTH[electrodeIndex].channelsPSTHs[entryindex].conditionPSTHs[cond].colorRGB[2]));

			for (int k=0;k<numSamplePoints-1;k++) 
			{
				// remap f_xi to pixels!
				float fx_pix = MIN(plotHeight, MAX(0,(f_xi[k]-axesRange[1])/rangeY * plotHeight));
				float fxp1_pix = MIN(plotHeight,MAX(0,(f_xi[k+1]-axesRange[1])/rangeY * plotHeight));
				if (valid[k] && valid[k+1])
					g.drawLine(x0+subsample*k, h-fx_pix-y0, x0+subsample*(k+1), h-fxp1_pix-y0);
			}

		}
	}

	tcb->unlockPSTH();


	repaint();
	
}

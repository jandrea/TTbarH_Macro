from ROOT import gROOT, TCanvas, TF1, TH1F, TFile, TGraph
from array import array

import numpy as n

dosysttable = True

dobiasscan  = False


options = Options()
options.set('minimizer', 'strategy', 'newton_vanilla')

# for model building:
def get_model(signalname):

    # Read in and build the model automatically from the histograms in the root file. 
    # This model will contain all shape uncertainties given according to the templates
    # which also includes rate changes according to the alternate shapes.
    # For more info about this model and naming conventuion, see documentation
    # of build_model_from_rootfile.

    model = build_model_from_rootfile('theta_histofiles.root',  include_mc_uncertainties=True)

    # If the prediction histogram is zero, but data is non-zero, teh negative log-likelihood
    # is infinity which causes problems for some methods. Therefore, we set all histogram
    # bin entries to a small, but positive value:
    model.fill_histogram_zerobins()

    # define what the signal processes are. All other processes are assumed to make up the 
    # 'background-only' model.
    model.set_signal_processes('TT')

    # Add some lognormal rate uncertainties. The first parameter is the name of the
    # uncertainty (which will also be the name of the nuisance parameter), the second
    # is the 'effect' as a fraction, the third one is the process name. The fourth parameter
    # is optional and denotes the channl. The default '*' means that the uncertainty applies
    # to all channels in the same way.
    # Note that you can use the same name for a systematic here as for a shape
    # systematic. In this case, the same parameter will be used; shape and rate changes 
    # will be 100% correlated.
    
    
    
    #model.add_lognormal_uncertainty('ttbar_rate', math.log(1.0), 'ttbar')
    #model.distribution.set_distribution_parameters('ttbar_rate', width=1000000) 
    

    #model.add_lognormal_uncertainty(' _rate', math.log(1.22), 'TT');	  
    model.add_lognormal_uncertainty('TTljets_rate',  math.log(2.), 'TTljets');    
    model.add_lognormal_uncertainty('Zjets_rate',     math.log(100), 'Zjets');     
    model.add_lognormal_uncertainty('barsChan_rate', math.log(1.3), 'barsChan');   
    model.add_lognormal_uncertainty('sChan_rate',    math.log(1.3), 'sChan');   
    model.add_lognormal_uncertainty('tChan_rate',    math.log(1.3), 'tChan');   
    model.add_lognormal_uncertainty('bartChan_rate', math.log(1.3), 'bartChan');   
    model.add_lognormal_uncertainty('tW_rate',       math.log(1.3), 'tW'); 
    model.add_lognormal_uncertainty('bartW_rate',    math.log(1.3), 'bartW');   
    model.add_lognormal_uncertainty('TTZ_rate',       math.log(1.3), 'TTZ'); 
    #model.add_lognormal_uncertainty('TTW_rate',       math.log(1.3), 'TTW'); 
    model.add_lognormal_uncertainty('WZ_rate',        math.log(1.3), 'WZ');   
    model.add_lognormal_uncertainty('ZZ_rate',        math.log(1.3), 'ZZ');   
    model.add_lognormal_uncertainty('WW_rate',        math.log(1.3), 'WW');   
    #model.add_lognormal_uncertainty('tZq_rate',       math.log(1.3), 'tZq'); 
	
	
    # the qcd model is from data, so do not apply a lumi uncertainty on that:
    for p in model.processes:
    	#if p == 'dy': continue
    	#if p == 'fake': continue
    	model.add_lognormal_uncertainty('lumi',        math.log(1.026), p)
	
        #model.add_lognormal_uncertainty('TrigLept',    math.log(1.013), p)
	
    for p in model.processes:
    	if p != 'TT': continue
    	#model.add_lognormal_uncertainty('fixedscale',        math.log(1.0151), p)
    	#model.add_lognormal_uncertainty('fixedmatching',     math.log(1.0149), p)
    
	
        #model.add_lognormal_uncertainty('Brs',     math.log(1.05) , p)
    # Specifying all uncertainties manually can be error-prone. You can also execute
    # a automatically generated file using python's execfile here
    # which contains these statements, or read in a text file, etc. Remember: this is a
    # python script, so use this power!
    return model

# -------------- TO CHANGE BY THE USER
signalname = 'TT'
# -------------- TO CHANGE BY THE USER
model = get_model(signalname)


# first, it is a good idea to generate a summary report to make sure everything has worked
# as expected. The summary will generate quite some information which should it make easy to spot
# errors like typos in the name of uncertainties, missing shape uncertaintie, etc.
model_summary(model)




# 2.b. CLs limits
# calculate cls limit plots. The interface is very similar to bayesian_limits. However, there are a few
# more options such as the definition of the test statistic which is usually a likelihood ratio but can differ in
# which parameters are minimized and which constraints / ranges are applied during minimization.
# Here, we stay with the default which fixes beta_signal=0
# for the background only hypothesis and lets it float freely for the signal+background hypothesis.
# See cls_limits documentation for more options.

#

signal_shapes = {'TT': ['TT']}  

one_sigma = 0.6827
two_sigma = 0.95

print ("measurement of the cross-section")
res = pl_interval(model, 'data', n=1, cls = [one_sigma], signal_process_groups = signal_shapes , options = options)
#twi keys 'TT' and the interval "one_sigma", it returns a list of double entries : lower and upper bound
print [ "%.3f" % res['TT'][0][0] , "%.3f" %res['TT'][one_sigma][0][0] , "%.3f" %res['TT'][one_sigma][0][1] ]

TT_init_xs = 245.8


TT_fit  = TT_init_xs*res['TT'][0][0]
TT_down = TT_init_xs*res['TT'][one_sigma][0][0]
TT_up   = TT_init_xs*res['TT'][one_sigma][0][1] 

print ["fitted cross section ", "%.1f" %TT_fit]
print ["down variation       ", "%.1f" %TT_down]
print ["up variation         ", "%.1f" %TT_up]


syst_down   = (res['TT'][0][0] - res['TT'][one_sigma][0][0])/res['TT'][0][0]
syst_up     = (res['TT'][one_sigma][0][1] - res['TT'][0][0])/res['TT'][0][0]

interval = (res['TT'][one_sigma][0][1] - res['TT'][one_sigma][0][0])/2


print ["systdown/up (%)" , "%.1f" %(syst_down*100), "%.1f" %(syst_up*100)]
print ["the interval is ", interval]
print ["final cross section ", "%.1f" %TT_fit, "-", "%.1f" %(syst_down*TT_fit), "+", "%.1f" %(syst_up*TT_fit)]

 
resnll = nll_scan(model, 'data', n=1,  npoints=100, range=[0.8, 1.2], options = options)


finalplot = resnll['TT'][0]

#print ["profile scan ", resnll['TT'][0].x ]

#x = n.linspace(0, 4*n.pi,101)
#y = n.cos(x)
xprofil =  array("d", resnll['TT'][0].x)
yprofil =  array("d", resnll['TT'][0].y)

graph_profile = TGraph(len(xprofil), xprofil, yprofil)
#graph_profile = TGraph(len(x), x,y)
histo_graph = TH1F("histo_graph", "histo_graph", 100, xprofil[0], xprofil[len(xprofil)-1]);
histo_graph.SetMaximum(graph_profile.GetMaximum());

finalplot.write_txt('PRL.txt')
#finalplot.histo()


print ("------------------------------------------------------------------")
print ("------------------------------------------------------------------")


### For max. Likelihood Fit results

print ("Run MLE")
signal_shapes = {'TT': ['TT']}
fit = mle(model, input = 'data', n = 1, signal_process_groups = signal_shapes, with_covariance=True, with_error=True, ks = True, chi2 = True, options = options)

# the output is (fitted value, uncertainty)
# The first numbers in the brackets show how far we are from the nominal value (which is 0) after the fit. 
#A value of 1 would mean 1 sigma deviation. So we are below 1 sigma deviation. 
#The second numbers in the brackets illustrates the uncertainty on the fitted value, it should be below 1, 
#and a value close to 1 corresponds to "no sensitivity" on the systematic.

print ("Determine nuisance parameters and their uncertainties")
parameter_values = {}
parameter_uncert = {}
#for p in model.get_parameters([]):
for p in model.get_parameters(['TT']):
    parameter_values[p] = fit['TT'][p][0][0]
    parameter_uncert[p] = fit['TT'][p][0][1]
    
    print [p, "%.4f" %parameter_values[p], "%.4f" %parameter_uncert[p] ]



parameter_values['beta_signal'] =  res['TT'][0][0]

print ("Create postfit histograms")

histos = evaluate_prediction(model, parameter_values, include_signal = True)
write_histograms_to_rootfile(histos, 'histos-mle_TT.root')

print ("------------------------------------------------------------------")
print ("------------------------------------------------------------------")

#############################################
#### Perform fit excluding one nuisance param
#############################################


if dosysttable:
	syst = 0
	tot_uncert =0

        print ["--------------------------------"]
	print ("Determine the impact of each systematic")
	for p in model.get_parameters([]):
		model_syst = model.copy()
		model_syst.distribution.set_distribution_parameters(p, width = 0.0, mean = parameter_values[p], range = [parameter_values[p], parameter_values[p]])
		res_syst = pl_interval(model_syst, 'data', n=1, cls = [one_sigma], signal_process_groups = signal_shapes, options = options  )
	
       		
		interval_syst = (res_syst['TT'][one_sigma][0][1] - res_syst['TT'][one_sigma][0][0])/2
		syst  = (abs(interval**2 - interval_syst**2))**(0.5)
		tot_uncert = tot_uncert + (syst)**2
		#print ["syst effect of (%)  ", p, "%.2f" %(syst*100)]
		#print ["syst effect of (pb) ", p, "%.2f" %(syst*TT_fit)]
		print [p, "%.2f" %(syst*TT_fit), "%.2f" %(syst*100)]
		
        	#print ["--------------------------------"]

	#print ["total syst down/up" ,"%.4f" % total_down**(0.5), "%.4f" %total_up**(0.5)]
	tot_uncert = tot_uncert**(0.5)
	print ["total uncert %" , tot_uncert*100]
	tot_uncert = tot_uncert*TT_fit
	print ["total uncert pb" , tot_uncert]


print ("------------------------------------------------------------------")
print ("------------------------------------------------------------------")

################################
#### Perform toy MC
################################

theBias0p5 = TH1F('theBias0p5', 'theBias0p5', 100, 0.3, 0.7)
theBias0p6 = TH1F('theBias0p6', 'theBias0p6', 100, 0.4, 0.8)
theBias0p7 = TH1F('theBias0p7', 'theBias0p7', 100, 0.5, 0.9)
theBias0p8 = TH1F('theBias0p8', 'theBias0p8', 100, 0.6, 1.0)
theBias0p9 = TH1F('theBias0p9', 'theBias0p9', 100, 0.7, 1.1)
theBias1p0 = TH1F('theBias1p0', 'theBias1p0', 100, 0.8, 1.2)
theBias1p1 = TH1F('theBias1p1', 'theBias1p1', 100, 0.9, 1.3)
theBias1p2 = TH1F('theBias1p2', 'theBias1p2', 100, 1.0, 1.4)
theBias1p3 = TH1F('theBias1p3', 'theBias1p3', 100, 1.1, 1.5)
theBias1p4 = TH1F('theBias1p4', 'theBias1p4', 100, 1.2, 1.6)
theBias1p5 = TH1F('theBias1p5', 'theBias1p5', 100, 1.3, 1.7)


thePull0p5 = TH1F('thePull0p5', 'thePull0p5', 200, -4, 4)
thePull0p6 = TH1F('thePull0p6', 'thePull0p6', 200, -4, 4)
thePull0p7 = TH1F('thePull0p7', 'thePull0p7', 200, -4, 4)
thePull0p8 = TH1F('thePull0p8', 'thePull0p8', 200, -4, 4)
thePull0p9 = TH1F('thePull0p9', 'thePull0p9', 200, -4, 4)
thePull1p0 = TH1F('thePull1p0', 'thePull1p0', 200, -4, 4)
thePull1p1 = TH1F('thePull1p1', 'thePull1p1', 200, -4, 4)
thePull1p2 = TH1F('thePull1p2', 'thePull1p2', 200, -4, 4)
thePull1p3 = TH1F('thePull1p3', 'thePull1p3', 200, -4, 4)
thePull1p4 = TH1F('thePull1p4', 'thePull1p4', 200, -4, 4)
thePull1p5 = TH1F('thePull1p5', 'thePull1p5', 200, -4, 4)

if dobiasscan:
	for i in range(11):
		print ("perform toy MC for bias scan")
		fixed_dist = get_fixed_dist(model.distribution)
		#mle(model, "toys:1.0", 1000, nuisance_prior_toys = fixed_dist)
		if i==0:
			#res_toy = pl_interval(model, 'toys:0.5', n=1100, cls = [one_sigma], signal_process_groups = signal_shapes, nuisance_prior_toys = fixed_dist )
			res_toy = pl_interval(model, 'toys:0.5', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes , options = options )
			for j in range(10000):
				theBias0p5.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 0.5)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull0p5.Fill(pull)
			#print ["%.4f" % res_toy['TT'][0][0], res_toy['TT'][one_sigma][0][1], res_toy['TT'][one_sigma][0][1]]
	        if i==1:
		        res_toy = pl_interval(model, 'toys:0.6', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes  , options = options)
		        for j in range(10000):
		       		theBias0p6.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 0.6)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull0p6.Fill(pull)
	        if i==2:
		        res_toy = pl_interval(model, 'toys:0.7', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes , options = options )
		        for j in range(10000):
			        theBias0p7.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 0.7)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull0p7.Fill(pull)
	        if i==3:
		        res_toy = pl_interval(model, 'toys:0.8', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes , options = options)
		        for j in range(10000):
			        theBias0p8.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 0.8)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull0p8.Fill(pull)
	        if i==4:
		        res_toy = pl_interval(model, 'toys:0.9', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes , options = options)
		        for j in range(10000):
			        theBias0p9.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 0.9)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull0p9.Fill(pull)
	        if i==5:
		        res_toy = pl_interval(model, 'toys:1.0', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes , options = options )
		        for j in range(10000):
			        theBias1p0.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 1.0)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull1p0.Fill(pull)
	        if i==6:
		        res_toy = pl_interval(model, 'toys:1.1', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes  , options = options)
		        for j in range(10000):
			        theBias1p1.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 1.1)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull1p1.Fill(pull)
	        if i==7:
		        res_toy = pl_interval(model, 'toys:1.2', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes  , options = options)
		        for j in range(10000):
			        theBias1p2.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 1.2)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull1p2.Fill(pull)
	        if i==8:
		        res_toy = pl_interval(model, 'toys:1.3', n=10101, cls = [one_sigma], signal_process_groups = signal_shapes  , options = options)
		        for j in range(10000):
			        theBias1p3.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 1.3)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull1p3.Fill(pull)
	        if i==9:
		        res_toy = pl_interval(model, 'toys:1.4', n=10100, cls = [one_sigma], signal_process_groups = signal_shapes , options = options)
		        for j in range(10000):
			        theBias1p4.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 1.4)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull1p4.Fill(pull)         
	        if i==10:
		        res_toy = pl_interval(model, 'toys:1.5', n=10101, cls = [one_sigma], signal_process_groups = signal_shapes  , options = options)
		        for j in range(10000):
			        theBias1p5.Fill(res_toy['TT'][0][j])
				pull = (res_toy['TT'][0][j] - 1.5)/(0.5*(res_toy['TT'][one_sigma][j][1] -res_toy['TT'][one_sigma][j][0]))
				thePull1p5.Fill(pull)
	       
	        print [ "%.4f" %res_toy['TT'][0][0] , "%.4f" %res_toy['TT'][one_sigma][0][0] , "%.4f" %res_toy['TT'][one_sigma][0][1] ] 



outputfile = TFile("output_pseudo.root", "recreate");
outputfile.cd()
theBias0p5.Write()
theBias0p6.Write()
theBias0p7.Write()
theBias0p8.Write()
theBias0p9.Write()
theBias1p0.Write()
theBias1p1.Write()
theBias1p2.Write()
theBias1p3.Write()
theBias1p4.Write()
theBias1p5.Write()

thePull0p5.Write()
thePull0p6.Write()
thePull0p7.Write()
thePull0p8.Write()
thePull0p9.Write()
thePull1p0.Write()
thePull1p1.Write()
thePull1p2.Write()
thePull1p3.Write()
thePull1p4.Write()
thePull1p5.Write()
histo_graph.Write()
graph_profile.Write()

report = model_summary(model)
#report.write_html('htmlout')

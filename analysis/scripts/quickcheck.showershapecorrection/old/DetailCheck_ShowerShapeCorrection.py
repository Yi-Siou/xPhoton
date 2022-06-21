#!/usr/bin/env python2

import ROOT
import json
import sys

import xPhoton.analysis.PlotObjectMgr as PlotObjectMgr
import ShowerShapeCorrectionBase as SSCB

def ShowRatioPlot(pad, etaregion, varname, figFrags=FigPartContainer()):
    hdata = ROOT.gROOT.FindObject( 'hdata.'+'_'.join([etaregion,varname]) )
    hsimu = ROOT.gROOT.FindObject( 'hsimu.'+'_'.join([etaregion,varname]) )
    hcalb = ROOT.gROOT.FindObject( 'hcalb.'+'_'.join([etaregion,varname]) )

    ratio_simu = hdata.Clone()
    ratio_simu.Divide(hsimu)
    ratio_simu.SetName( 'ratio.%s'%hsimu.GetName() )
    PlotObjectMgr.HistSetting_Clone(ratio_simu, hsimu)
    #ratio_simu.SetMarkerStyle(32)
    ratio_simu.SetMarkerStyle(0)
    ratio_simu.SetMarkerColor( ratio_simu.GetLineColor() )
    ratio_simu.SetMarkerSize(4)
    ratio_simu.SetFillStyle(0)
    SSCB.HistSetting_Visualization_LowerStyling(ratio_simu)



    ratio_calb = hdata.Clone()
    ratio_calb.Divide(hcalb)
    ratio_calb.SetName( 'ratio.%s'%hcalb.GetName() )
    PlotObjectMgr.HistSetting_Clone(ratio_calb, hcalb)
    #ratio_calb.SetMarkerStyle(24)
    ratio_calb.SetMarkerStyle(0)
    ratio_calb.SetMarkerColor( ratio_calb.GetLineColor() )
    ratio_calb.SetMarkerSize(4)
    ratio_calb.SetFillStyle(0)

    # put 100x error to check error bar is printed or not.
    #[ ratio_calb.SetBinError( ibin, ratio_calb.GetBinError(ibin) * 100.) for ibin in range(1, ratio_calb.GetNbinsX()+1) ]

    pad.cd()
    ratio_simu.Draw('e0 p')
    ratio_calb.Draw('ep 0 same')

    figFrags.KeepPlotable(ratio_simu)
    figFrags.KeepPlotable(ratio_calb)
    return figFrags

def ShowOriginalDist(pad, etaregion, varname, figFrags=FigPartContainer()):
    hdata = ROOT.gROOT.FindObject( 'hdata.'+'_'.join([etaregion,varname]) )
    hsimu = ROOT.gROOT.FindObject( 'hsimu.'+'_'.join([etaregion,varname]) )
    hcalb = ROOT.gROOT.FindObject( 'hcalb.'+'_'.join([etaregion,varname]) )

    PlotObjectMgr.HistSetting_Visualization_data( hdata, LineWidth_ =2 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hdata, xlabel_=varname, ylabel_='Entries / %.1e' % hdata.GetBinWidth(1) )

    PlotObjectMgr.HistSetting_Visualization_MC  ( hsimu, LineColor_ = 38 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hsimu, xlabel_=varname, ylabel_='Entries / %.1e' % hsimu.GetBinWidth(1) )
    hsimu.Scale( hdata.Integral() / hsimu.Integral() )

    PlotObjectMgr.HistSetting_Visualization_MC  ( hcalb, LineColor_ = 30 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hcalb, xlabel_=varname, ylabel_='Entries / %.1e' % hcalb.GetBinWidth(1) )
    hcalb.Scale( hdata.Integral() / hcalb.Integral() )

    leg=ROOT.TLegend( 0.2, 0.67, 0.8, 0.85 )
    leg.SetTextAlign(32)
    leg.AddEntry( hdata, 'UL2018 data sample', 'lp' )
    leg.AddEntry( hsimu, 'original MC. #chi^{2} = %.2e / %.0f = %.2e' % (
        Chi2(hdata.GetName(),hsimu.GetName()), Ndof(hdata.GetName()), Chi2(hdata.GetName(),hsimu.GetName()) / Ndof(hdata.GetName())
        ), 'l')
    leg.AddEntry( hcalb, 'calibrated MC. #chi^{2} = %.2e / %.0f = %.2e' % (
        Chi2(hdata.GetName(),hcalb.GetName()), Ndof(hdata.GetName()), Chi2(hdata.GetName(),hcalb.GetName()) / Ndof(hdata.GetName())
        ), 'l')

    leg.SetBorderSize(0)
    leg.SetFillColor(4000)
    leg.SetFillStyle(4000)

    pad.cd()
    hdata.GetXaxis().SetLabelSize(0)
    hdata.Draw('axis')
    hsimu.Draw('hist same')
    hcalb.Draw('hist same')
    hdata.Draw('e0 p same')
    leg.Draw()

    figFrags.KeepPlotable(hdata)
    figFrags.KeepPlotable(hsimu)
    figFrags.KeepPlotable(hcalb)
    figFrags.KeepPlotable( leg )
    return figFrags


if __name__ == "__main__":
    args = SSCB.JsonInfo(sys.argv[1])
    fdata = ROOT.TFile.Open( args.file_data )
    tdata = fdata.Get('t')

    fsimu = ROOT.TFile.Open( args.file_simu )
    tsimu = fsimu.Get('t')

    from xPhoton.analysis.MyCanvas import MyCanvas
    canv=MyCanvas('canv',1600,1200)

    import xPhoton.analysis.SelectionsMgr as Selections
    pre_selections=(
        Selections.DrawCutStr_ZmassWindow(),
        Selections.DrawCutStr_data_PurifyZ(),
        )
    listofvars=[]

    for eta in ('barrel','endcap'):
        varname='mva'
        selections=[ Selections.DrawCutStr_EtaRegion(eta) ]
        selections.extend(pre_selections)
        cut='&&'.join( selections )

        hsetting='(10,-1.,1.)'
        listofvars.append( (varname, eta) )
        tdata.Draw('mva                           >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('mva_nocorr                    >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('mva                           >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,0.05)'
        varname='scEtaWidth'
        listofvars.append( (varname, eta) )
        tdata.Draw('scEtaWidth                    >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('scEtaWidth                    >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_scEtaWidth              >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,0.2)'
        varname='scPhiWidth'
        listofvars.append( (varname, eta) )
        tdata.Draw('scPhiWidth                    >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('scPhiWidth                    >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_scPhiWidth              >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,1.2)'
        varname='r9Full5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('r9Full5x5                     >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('r9Full5x5                     >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_r9Full5x5               >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.2,1.)'
        varname='s4Full5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('s4Full5x5                     >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('s4Full5x5                     >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_s4Full5x5               >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.002,0.045)'
        varname='sieieFull5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('sieieFull5x5                  >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('sieieFull5x5                  >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_sieieFull5x5            >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,-0.0015,0.0015)' if eta == 'endcap' else '(40,-0.0002,0.0002)'
        varname='sieipFull5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('sieipFull5x5                  >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('sieipFull5x5                  >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_sieipFull5x5            >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,1.)'
        varname='esEnergyOverSCRawEnergy'
        listofvars.append( (varname, eta) )
        tdata.Draw('esEnergyOverSCRawEnergy       >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('esEnergyOverSCRawEnergy       >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_esEnergyOverSCRawEnergy >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

    canv.Clear()
    upperpad=PlotObjectMgr.UpperPad()
    lowerpad=PlotObjectMgr.LowerPad()
    canv.cd()
    upperpad.Draw()
    lowerpad.Draw()

    for vname, etaregion in listofvars:
        canv.cd()
        figFrag=FigPartContainer()
        ShowOriginalDist(upperpad, etaregion, vname, figFrag)
        ShowRatioPlot(lowerpad, etaregion, vname, figFrag)

        canv.SaveAs('ratioplot.%s_%s.pdf' % (etaregion,vname) )
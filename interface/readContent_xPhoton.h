#ifndef __READGGANALYSIS_XPHOTON_H__
#define __READGGANALYSIS_XPHOTON_H__
// you can only load ONE readBrahBrah.h in the analysis.
#include <vector>

enum var{
    jetSubVtxPt   ,
    jetSubVtxMass ,
    jetSubVtx3DVal,
    jetSubVtx3DErr  ,
    jetSubVtxNtrks,
    run,
    event,
    isData,
    HLT,
    HLTIsPrescaled,
    HLT50ns,
    HLTIsPrescaled50ns,
    phoFiredTrg,
    pthat,
    genHT,
    mcPt,
    mcEta,
    mcPhi,
    mcCalIso04,
    mcTrkIso04,
    recoPt,
    recoEta,
    recoPhi,
    recoSCEta,
    r9,
    isMatched,
    isMatchedEle,
    isConverted,
    idLoose,
    idMedium,
    idTight,
    nVtx,
    nPU,
    puwei,
    eleVeto,
    HoverE,
    sieie,
    sieip,
    sipip,
    chIso,
    phoIso,
    nhIso,
    chIsoRaw,
    chWorstRaw,
    phoIsoRaw,
    nhIsoRaw,
    rho,
    e1x3,
    e2x2,
    e2x5,
    e5x5,
    rawE,
    scEtaWidth,
    scPhiWidth,
    esRR,
    esEn,
    mva,
    photonIDmva,
    phoIDbit,
    mva_hgg,
    HggPresel,
    Mmm,
    Mee,
    MET,
    metFilters,
    METPhi,
    phohasPixelSeed,
    MTm,
    MTe,
    deta_wg,
    dphi_wg,
    sieieFull5x5,
    sieipFull5x5,
    sipipFull5x5,
    e1x3Full5x5,
    r9Full5x5,
    e2x2Full5x5,
    e2x5Full5x5,
    e5x5Full5x5,
    jetPt,
    jetEta,
    jetPhi,
    jetY,
    jetJECUnc,
    jetGenJetPt,
    jetGenJetEta,
    jetGenJetPhi,
    jetGenJetY,
    jetCSV2BJetTags,
    jetDeepCSVTags_b,
    jetDeepCSVTags_bb,
    jetDeepCSVTags_c,
    jetDeepCSVTags_udsg,
    jetPartonID,
    jetGenPartonID,
    jetHadFlvr,
    xsweight,
    photon_jetID,
    SeedTime,
    SeedEnergy,
    MIPTotEnergy,
    totVar
};

std::vector<const char*> varBRANCHES={
    "jetSubVtxPt"   ,
    "jetSubVtxMass" ,
    "jetSubVtx3DVal",
    "jetSubVtx3DErr"  ,
    "jetSubVtxNtrks",
    "run",
    "event",
    "isData",
    "HLT",
    "HLTIsPrescaled",
    "HLT50ns",
    "HLTIsPrescaled50ns",
    "phoFiredTrg",
    "pthat",
    "genHT",
    "mcPt",
    "mcEta",
    "mcPhi",
    "mcCalIso04",
    "mcTrkIso04",
    "recoPt",
    "recoEta",
    "recoPhi",
    "recoSCEta",
    "r9",
    "isMatched",
    "isMatchedEle",
    "isConverted",
    "idLoose",
    "idMedium",
    "idTight",
    "nVtx",
    "nPU",
    "puwei",
    "eleVeto",
    "HoverE",
    "sieie",
    "sieip",
    "sipip",
    "chIso",
    "phoIso",
    "nhIso",
    "chIsoRaw",
    "chWorstRaw",
    "phoIsoRaw",
    "nhIsoRaw",
    "rho",
    "e1x3",
    "e2x2",
    "e2x5",
    "e5x5",
    "rawE",
    "scEtaWidth",
    "scPhiWidth",
    "esRR",
    "esEn",
    "mva",
    "photonIDmva",
    "phoIDbit",
    "mva_hgg",
    "HggPresel",
    "Mmm",
    "Mee",
    "MET",
    "metFilters",
    "METPhi",
    "phohasPixelSeed",
    "MTm",
    "MTe",
    "deta_wg",
    "dphi_wg",
    "sieieFull5x5",
    "sieipFull5x5",
    "sipipFull5x5",
    "e1x3Full5x5",
    "r9Full5x5",
    "e2x2Full5x5",
    "e2x5Full5x5",
    "e5x5Full5x5",
    "jetPt",
    "jetEta",
    "jetPhi",
    "jetY",
    "jetJECUnc",
    "jetGenJetPt",
    "jetGenJetEta",
    "jetGenJetPhi",
    "jetGenJetY",
    "jetCSV2BJetTags",
    "jetDeepCSVTags_b",
    "jetDeepCSVTags_bb",
    "jetDeepCSVTags_c",
    "jetDeepCSVTags_udsg",
    "jetPartonID",
    "jetGenPartonID",
    "jetHadFlvr",
    "xsweight",
    "photon_jetID",
    "SeedTime",
    "SeedEnergy",
    "MIPTotEnergy",
};


#endif

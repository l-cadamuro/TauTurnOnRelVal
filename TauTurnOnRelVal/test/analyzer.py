#import FWCore.ParameterSet.VarParsing as VarParsing
#import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms
process = cms.Process("RelValTauL1")

is80X = True

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if is80X:
  process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_v20'
  process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/FEBC4F3B-8E98-E611-881F-0CC47A4D766C.root',
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/4CB37ED1-8E98-E611-B36C-0CC47A7452DA.root',
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/3C932A4B-8F98-E611-814E-0CC47A4D76B6.root',
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/24D05AE6-8F98-E611-9F9A-0025905A60D2.root',
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/400FA080-9198-E611-B675-0CC47A7AB7A0.root',
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/F8FCC5DC-9198-E611-B84A-0CC47A4D768E.root',
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/CC7D9CED-A098-E611-8F1B-0025905A608E.root',
        # '/store/relval/CMSSW_8_0_21/RelValZTT_13/GEN-SIM-RECO/PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1/10000/1E8C2AEB-A098-E611-A0CC-0CC47A4C8F08.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/1E8C2AEB-A098-E611-A0CC-0CC47A4C8F08.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/24D05AE6-8F98-E611-9F9A-0025905A60D2.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/3C932A4B-8F98-E611-814E-0CC47A4D76B6.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/400FA080-9198-E611-B675-0CC47A7AB7A0.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/4CB37ED1-8E98-E611-B36C-0CC47A7452DA.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/CC7D9CED-A098-E611-8F1B-0025905A608E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/F8FCC5DC-9198-E611-B84A-0CC47A4D768E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-RECO/FEBC4F3B-8E98-E611-881F-0CC47A4D766C.root',
      ),
      secondaryFileNames = cms.untracked.vstring(
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/3055CDCA-8498-E611-83A9-0025905A605E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/02A5A6C0-8498-E611-A7B1-0CC47A74524E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/0808BA30-8498-E611-8B93-0025905A48BA.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/0AC4D097-8498-E611-869A-0CC47A4D7644.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/0E4CAB27-8498-E611-BCA5-0CC47A4C8F2C.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/0EC70BC4-8498-E611-8ADF-0CC47A78A33E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/10996587-8498-E611-BF25-0CC47A78A45A.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/10A453C0-8498-E611-8C06-0025905B857C.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/10ED8635-8498-E611-BAF4-0025905A6088.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/123F6F35-8498-E611-A52D-0025905B8576.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/140D01C9-8498-E611-A0B3-003048FFD798.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/169D9DBD-8498-E611-9F9F-0025905A48EC.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/182EBA2C-8498-E611-83A0-0025905B85F6.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/185FA6C3-8498-E611-A7D5-0025905B85AE.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/2033E22E-8498-E611-9F8D-0025905B85B2.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/22EF5B0F-8598-E611-BBDA-0CC47A4D760A.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/2CA9B92A-8498-E611-B0B7-0025905A607A.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/3661DA2E-8498-E611-B9D1-0025905B8562.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/36DF7326-8498-E611-A6BD-0CC47A4D7618.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/3C22FCB8-8498-E611-A184-0025905B8564.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/3C6866C2-8498-E611-9209-0025905B85C0.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/3ED59FBF-8498-E611-8373-0025905B858E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/4293772B-8498-E611-A2B9-0025905B85F6.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/44A3B1BB-8498-E611-83CB-0CC47A7C34C4.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/48402836-8498-E611-8556-0025905B85D0.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/4A0A9312-8598-E611-A0D7-003048FFD71C.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/5CB09214-8598-E611-9786-0025905B8606.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/68712CAE-8498-E611-8BF0-0CC47A4D7630.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/6EFEFEBB-8498-E611-8BD0-0025905B8612.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/70DBBAB2-8498-E611-9921-0025905B858E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/7249945F-8498-E611-9AB4-0025905AA9CC.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/8626D42E-8498-E611-9CD5-0025905B8600.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/886CD3B9-8498-E611-B608-0CC47A7C3428.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/8C2B14A7-8498-E611-9CA3-0025905B8590.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/8E32B02A-8498-E611-A34C-0025905A607A.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/8E4AADBF-8498-E611-9851-0025905B8562.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/9AC3092F-8498-E611-9894-0025905B8562.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/9C627DB0-8498-E611-A330-0CC47A4C8E26.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/9CF07CC8-8498-E611-8AF0-003048FFD722.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/A0EB97B3-8498-E611-B6E6-0CC47A4D76C8.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/A4551F28-8498-E611-9A26-0CC47A4D7604.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/AC15B4A7-8498-E611-A742-0025905B85D2.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/AE12AFA8-8498-E611-B6EE-0CC47A7C34A6.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/B0C710A9-8498-E611-9C97-0CC47A4D7668.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/B473731E-8498-E611-AC93-0CC47A4D768E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/B474F80F-8598-E611-86A8-0025905A48F2.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/C28C502E-8498-E611-A3FF-0025905A6068.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/C28DFDB1-8498-E611-A29F-0025905B8600.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/CA2985AE-8498-E611-8097-0CC47A7C3604.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/D276272B-8498-E611-9E8C-0CC47A4C8F2C.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/D8A991C8-8498-E611-8AC6-0025905A6080.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/DAB3659D-8498-E611-974D-0025905B859E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/DE8E0ECA-8498-E611-A3CA-0025905B8606.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/E2A7F02A-8498-E611-9838-0CC47A7C340C.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/E6952AB3-8498-E611-817F-0025905B85D6.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/ECD4BBA0-8498-E611-8CE5-0025905A6126.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/ECE93B06-8598-E611-BAE4-0CC47A4D7654.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/F0A9392C-8498-E611-8093-0CC47A4C8E5E.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/F0B4A799-8498-E611-98A0-0CC47A4D7678.root',
        'file:/data_CMS/cms/cadamuro/RelValZTT_13__CMSSW_8_0_21-PU25ns_80X_mcRun2_asymptotic_2016_TrancheIV_v6_Tr4GT_v6-v1__GEN-SIM-DIGI-RAW-HLTDEBUG/F89AD5A5-8498-E611-993B-0025905A6094.root',
      )
  )

else:
  process.GlobalTag.globaltag = '90X_mcRun2_asymptotic_v5'
  process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/EE445371-7810-E711-86D9-0CC47A7C345C.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/8EEA2072-7810-E711-ABF6-0025905A610A.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/F425E50A-1110-E711-B821-0CC47A4D7628.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/0C073C1F-1110-E711-B79A-0CC47A4C8E28.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/663779D8-1210-E711-9006-0CC47A78A4B8.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/D035C60F-1210-E711-867E-0CC47A78A2EC.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/AC5D5211-1210-E711-80FA-0CC47A4D7628.root',
        '/store/relval/CMSSW_9_0_0/RelValZTT_13/GEN-SIM-RECO/PU25ns_90X_mcRun2_asymptotic_v5-v1/00000/0099F6EB-1210-E711-A364-0CC47A78A458.root',
      )
  )

#### plugin 
process.load('TauTurnOnRelVal.TauTurnOnRelVal.MCanalysis_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)


#print particles gen level - DEBUG purposes
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(10),
  printVertex = cms.untracked.bool(False),
  src = cms.InputTag("genParticles")
)


process.p = cms.Path(
    process.TauSeq + 
    # process.printTree
    process.NtupleSeq
)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string('TauL1RelVal_hadtaus.root'))

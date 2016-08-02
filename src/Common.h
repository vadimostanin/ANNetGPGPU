#pragma once

#include <iostream>
#include <vector>


namespace ANN {
template <class T> class AbsLayer;
template <class T> class AbsNeuron;

template <typename T> void SetEdgesToValue(AbsLayer<T> *pSrcLayer, AbsLayer<T> *pDestLayer, const T &fVal, const bool &bAdaptState) {
	AbsNeuron<T> *pCurNeuron;
	Edge<T> *pCurEdge;
	for(unsigned int i = 0; i < pSrcLayer->GetNeurons().size(); i++) {
		pCurNeuron = pSrcLayer->GetNeurons().at(i);
		for(unsigned int j = 0; j < pCurNeuron->GetConsO().size(); j++) {
			pCurEdge = pCurNeuron->GetConO(j);
			// outgoing edge is connected with pDestLayer ..
			if(pCurEdge->GetDestination(pCurNeuron)->GetParent() == pDestLayer) {
				// .. d adapt only these edges
				pCurEdge->SetValue( fVal );
				pCurEdge->SetAdaptationState( bAdaptState );
			}
		}
	}
}

template <typename T> void Connect(AbsNeuron<T> *pSrcNeuron, AbsNeuron<T> *pDstNeuron, const bool &bAdaptState) {
	Edge<T> *pCurEdge = new Edge<T>(pSrcNeuron, pDstNeuron);
	pCurEdge->SetAdaptationState(bAdaptState);
	pSrcNeuron->AddConO(pCurEdge);
	pDstNeuron->AddConI(pCurEdge);
}

template <typename T> void Connect(AbsNeuron<T> *pSrcNeuron, AbsNeuron<T> *pDstNeuron, const T &fVal, const T &fMomentum, const bool &bAdaptState) {
	Edge<T> *pCurEdge = new Edge<T>(pSrcNeuron, pDstNeuron, fVal, fMomentum, bAdaptState);
	pSrcNeuron->AddConO(pCurEdge);
	pDstNeuron->AddConI(pCurEdge);
}

template <typename T> void Connect(AbsNeuron<T> *pSrcNeuron, AbsLayer<T> *pDestLayer, const std::vector<T> &vValues, const std::vector<T> &vMomentums, const bool &bAdaptState) {
	unsigned int iSize = pDestLayer->GetNeurons().size();
	unsigned int iProgCount = 1;

	for(int j = 0; j < static_cast<int>(iSize); j++) {
		if(iSize >= 10) {
			if(((j+1) / (iSize/10)) == iProgCount && (j+1) % (iSize/10) == 0) {
				std::cout<<"Building connections.. Progress: "<<iProgCount*10.f<<"%/Step="<<j+1<<std::endl;
				iProgCount++;
			}
		} else {
			std::cout<<"Building connections.. Progress: "<<(T)(j+1)/(T)iSize*100.f<<"%/Step="<<j+1<<std::endl;
		}
		ANN::Connect(pSrcNeuron, pDestLayer->GetNeuron(j), vValues[j], vMomentums[j], bAdaptState);
	}
}

template <typename T> void Connect(AbsNeuron<T> *pSrcNeuron, AbsLayer<T> *pDestLayer, const bool &bAdaptState) {
	unsigned int iSize = pDestLayer->GetNeurons().size();
	unsigned int iProgCount = 1;

	for(int j = 0; j < static_cast<int>(iSize); j++) {
		if(iSize >= 10) {
			if(((j+1) / (iSize/10)) == iProgCount && (j+1) % (iSize/10) == 0) {
				std::cout<<"Building connections.. Progress: "<<iProgCount*10.f<<"%/Step="<<j+1<<std::endl;
				iProgCount++;
			}
		} else {
			std::cout<<"Building connections.. Progress: "<<(T)(j+1)/(T)iSize*100.f<<"%/Step="<<j+1<<std::endl;
		}
		ANN::Connect(pSrcNeuron, pDestLayer->GetNeuron(j), bAdaptState);
	}
}

};
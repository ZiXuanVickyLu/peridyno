#pragma once
#include "ElastoplasticityModule.h"

namespace dyno {

	template<typename TDataType> class SummationDensity;

	template<typename TDataType>
	class FractureModule : public ElastoplasticityModule<TDataType>
	{
		DECLARE_TCLASS(ElastoplasticityModule, TDataType)
	public:
		typedef typename TDataType::Real Real;
		typedef typename TDataType::Coord Coord;
		typedef typename ::dyno::TBond<TDataType> Bond;

		FractureModule();
		~FractureModule() override {};

		void applyPlasticity() override;
	};
}
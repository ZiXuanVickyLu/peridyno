#include "FieldBase.h"
#include <algorithm>

#include "Module.h"

namespace dyno
{
	void FieldBase::setParent(Base* owner)
	{
		mOwner = owner;
	}

	Base* FieldBase::parent()
	{
		return mOwner;
	}

	void FieldBase::setSource(FieldBase* source)
	{
		m_derived = source == nullptr ? false : true;
		mSource = source;
	}

	FieldBase* FieldBase::getSource()
	{
		return mSource;
	}

	void FieldBase::addSink(FieldBase* f)
	{
		auto it = std::find(mSinks.begin(), mSinks.end(), f);

		if (it == mSinks.end())
		{
			mSinks.push_back(f);

//			f->setDerived(true);
			f->setSource(this);
		}
	}

	void FieldBase::removeSink(FieldBase* f)
	{
		auto it = std::find(mSinks.begin(), mSinks.end(), f);
		
		if (it != mSinks.end())
		{
			mSinks.erase(it);

//			f->setDerived(false);
			f->setSource(nullptr);
		}
	}

	bool FieldBase::isDerived()
	{
		return m_derived;
	}

	bool FieldBase::isAutoDestroyable()
	{
		return m_autoDestroyable;
	}

	void FieldBase::setAutoDestroy(bool autoDestroy)
	{
		m_autoDestroyable = autoDestroy;
	}

	void FieldBase::setDerived(bool derived)
	{
		m_derived = derived;
	}

	bool FieldBase::connectField(FieldBase* dst)
	{
		if (dst->getSource() != nullptr && dst->getSource() != this)
		{
			dst->getSource()->removeSink(dst);
		}

		this->addSink(dst);

		return true;
	}

	FieldBase* FieldBase::getTopField()
	{
		return mSource == nullptr ? this : mSource->getTopField();
	}

	void FieldBase::update()
	{
		if (!this->isEmpty() && callbackFunc != nullptr)
		{
			callbackFunc();
		}

		auto& sinks = this->getSinks();

		for each (auto var in sinks)
		{
			if (var != nullptr)
			{
				var->update();
			}
		}
	}

	bool FieldBase::isModified()
	{
		return m_modified;
	}

	void FieldBase::tagModified(bool modifed)
	{
		m_modified = modifed;
	}

	bool FieldBase::isOptional()
	{
		return m_optional;
	}

	void FieldBase::tagOptional(bool optional)
	{
		m_optional = optional;
	}

	FieldBase::FieldBase(std::string name, std::string description, FieldTypeEnum type, Base* parent)
	{
		m_name = name; m_description = description;
		m_fType = type;
		if (parent != nullptr)
		{
			parent->attachField(this, name, description, false);
		}
	}

	FieldTypeEnum FieldBase::getFieldType()
	{
		return m_fType;
	}

}


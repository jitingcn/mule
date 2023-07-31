#pragma once

#ifndef STRING_OBJECT_H__
#define STRING_OBJECT_H__

#include "Object.h"

namespace mule
{
	namespace Data
	{
		namespace Basic
		{

			/**
			 * @brief String is not a typical object cause it holds a variable length.
			 * For this reason, it is a subclass of Object.
			 * It should not be linked to the chain of Field.
			*/
			class String : public Object
			{
			protected:
				size_t lastSize;
			public:
				// ͨ�� Object �̳�
				virtual void Read(xybase::Stream *stream, DataHandler *dataHandler) override;
				virtual void Write(xybase::Stream *stream, DataHandler *dataHandler) override;
				virtual size_t Size() const override;
				virtual std::string GetTypeName() const override;

				virtual size_t GetLastSize() const override;
				virtual size_t EvalSize(const MultiValue &obj) const override;
			};
		}
	}
}

#endif

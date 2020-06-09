
#include "BaseModel.h"


		void BaseModel::SetTransform(Transform* _transform)
		{
			transform = _transform;
		}

		BaseModel::BaseModel()
		{
			transform = nullptr;
		}

		const std::vector<Mesh*>* BaseModel::GetMesh()
		{
			return &meshList;
		}
#pragma once
namespace kob
{
	class GameObject;

	class Component
	{
	public:
		//--------------------------------------------------
		//    Constructor and Destructor
		//--------------------------------------------------
		explicit Component(GameObject& parent);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		virtual void Start();
		virtual void Update() = 0;
		virtual void LateUpdate();
		virtual void FixedUpdate();
		virtual void Render()				const;
		virtual void ImGuiRenderUpdate();

		virtual void OnCollisionEnter(GameObject& other);
		virtual void OnCollisionExit(GameObject& other);
		virtual void OnCollisionStay(GameObject& other);

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		void FlagForDeletion();
		[[nodiscard]] bool IsFlaggedForDeletion()			const;
		[[nodiscard]] GameObject* GetGameObject() const;
		bool isActive = true;

	private:
		GameObject* m_pParent{};
		bool m_DeletionFlag{ false };
	};
}

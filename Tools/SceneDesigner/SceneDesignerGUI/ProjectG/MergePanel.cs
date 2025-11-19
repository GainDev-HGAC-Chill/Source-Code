using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Emergent.Gamebryo.SceneDesigner.Framework;
using Emergent.Gamebryo.SceneDesigner.PluginAPI;
using Emergent.Gamebryo.SceneDesigner.PluginAPI.StandardServices;

namespace Emergent.Gamebryo.SceneDesigner.GUI.ProjectG
{
	public partial class MergePanel : Form
	{
	
		//public
		public MergePanel()
		{
			InitializeComponent();
		}

		public MergePanel(string strFilepath)
		{
			//m_pmScene.Dispose();
			m_strGsaFilePath = strFilepath;
			InitializeComponent();
			ParsingGSA();
			m_tbNewSelectionSet.Hide();
			//m_tbNewSelectionSet
		}
	
		//private
		private void ParsingGSA()
		{
			m_pmScene = MFramework.Instance.Merge.ParsingGSA(m_strGsaFilePath);
			MEntity[] amEntities = m_pmScene.GetEntities();
			MSelectionSet[] amSets = m_pmScene.GetSelectionSets();

			foreach(MEntity pmEntity in amEntities)
			{// For all entities (모든 엔티티에 대해)
				// Retrieve the entities property name (엔티티의 프로퍼티네임들을 얻어옴)
				//String[] amPropertyNames = pmEntity.GetPropertyNames();
				//bool bIsRemoved = false;
				//foreach (String pmPropName in amPropertyNames)
				//{// For all property names (모든 프로퍼티네임들에 대해)
				//    if ("Light Type" == pmPropName)
				//    {// Light Type (라이트 타입이면)
				//        // Remove from scene (씬에서 제거)
				//        m_pmScene.RemoveEntity(pmEntity, false);
				//        foreach (MSelectionSet pmSets in amSets)
				//        {// For every selection set (모든 셀렉션셋들에 대해)
				//            if (null != pmSets.GetEntityByName(pmEntity.Name))
				//            {// If three have that entity (셋이 해당 엔티티를 가지고 있으면)
				//                // Remove that entity from set (셋에서 해당 엔티티 제거)
				//                pmSets.RemoveEntity(pmEntity);
				//            }
				//        }
				//        bIsRemoved = true;
				//        break;
				//    }
				//}

				//if (false == bIsRemoved)
				{// If it is not the entity removed from loop (이번 루프에서 제거된 엔티티가 아니면)
					// Get PG property type (PG프로퍼티 타입을 가져옴)
					String kPropType = MFramework.Instance.Merge.ParsingPGPropertyType(pmEntity);
					if ("" != kPropType)
					{// If the PG property type exists (PG프로퍼티 타입이 존재하면)
						// Set the entity property type correctly (엔티티의 프로퍼티 타입을 제대로 셋팅)
						pmEntity.PGProperty = (MEntity.ePGProperty)Enum.Parse(
							typeof(MEntity.ePGProperty),
							kPropType);
					}
				}
			}

			BuildEntryList(m_pmScene);
			BuildSelectionSetList(m_pmScene);
		}

		// Create an entity list (엔티티 리스트를 만든다.)
		private void BuildEntryList(MScene pmScene)
		{
			MEntity[] amEntities = pmScene.GetEntities();
			uint iEntityCount = pmScene.EntityCount;

			m_pmEntityList.Clear();

			foreach (MEntity pmEntity in amEntities)
			{// For all entities (모든 엔티티에 대해)
				bool bAdd = true;

				if ((m_eFilterState == FilterState.Hidden &&
						!pmEntity.Hidden) ||
					(m_eFilterState == FilterState.Frozen &&
						!pmEntity.Frozen) ||
					(m_eFilterState == FilterState.Visible &&
						(pmEntity.Hidden || pmEntity.Frozen)))
				{// Hidden, Frozen (히든, 프로즌 이면...)
					bAdd = false;
				}

				if (bAdd)
				{ //
					m_pmEntityList.Add(pmEntity);
				}
			}

			m_pmEntityList.Sort(m_pmEntityComparer);

			m_lbEntityList.BeginUpdate();
			int iTopIndex = m_lbEntityList.TopIndex;
			m_lbEntityList.Items.Clear();
			foreach (object pmObject in m_pmEntityList)
			{
				m_lbEntityList.Items.Add(pmObject);
			}
			m_lbEntityList.TopIndex = iTopIndex;
			m_lbEntityList.EndUpdate();
		}

		// Create a sub-section list (셀렉션셋 리스트를 만든다.)
		private void BuildSelectionSetList(MScene pmScene)
		{
			MSelectionSet[] amSelectionSet = pmScene.GetSelectionSets();
			uint iSelectionSetCount = pmScene.SelectionSetCount;

			m_pmSelectionSetList.Clear();

			foreach (MSelectionSet pmSelectionSet in amSelectionSet)
			{
				m_pmSelectionSetList.Add(pmSelectionSet);
			}

			m_pmSelectionSetList.Sort(m_pmSelectionSetComparer);

			m_lbSelectionSetList.BeginUpdate();
			int iTopindex = m_lblSelectionSetList.TabIndex;
			m_lbSelectionSetList.Items.Clear();
			foreach(object pmObject in m_pmSelectionSetList)
			{
				m_lbSelectionSetList.Items.Add(pmObject);
			}
			m_lbSelectionSetList.TopIndex = iTopindex;
			m_lbSelectionSetList.EndUpdate();
		}

		private void m_btnMerge_Click(object sender, EventArgs e)
		{
			string kNewSelSetName = null;
			MSelectionSet kNewSelSet = null;

			if(true==m_bGetByNewSelSetName)
			{// If the new selection set add-on is turned on (새 셀렉션셋 추가 기능이 켜져 있으면)
				kNewSelSetName = m_tbNewSelectionSet.Text;
				kNewSelSet = MSelectionSet.Create(kNewSelSetName);
				bool bIsAllSpace = true;
				int iNameIndex = 0;
				for (iNameIndex = 0; iNameIndex < kNewSelSetName.Length; ++iNameIndex)
				{// New selection set name (새 셀렉션 셋이름으로 넣은 문자열이)
					// Check if everything is blank (모두 공백인지 체크)
					bIsAllSpace &= (' ' == kNewSelSetName[iNameIndex]);
					if (false == bIsAllSpace)
						break;
				}
				if ((null == kNewSelSetName) || (true==bIsAllSpace))
				{
					MessageBox.Show("SelectionSet이름을 정해야 합니다.", "오류");
					return;
				}
				// Cuts all previous blank space (앞의 쓸데없는 공백들을 다 잘라냄)
				kNewSelSetName = kNewSelSetName.Substring(iNameIndex);
			}

			for (int iEntityIndex = 0; iEntityIndex < m_lbEntityList.Items.Count; ++iEntityIndex)
			{// Of all entities (모든 엔티티들 중에...)
				if (true == m_lbEntityList.GetSelected(iEntityIndex))
				{// Selected entities are (선택된 엔티티는...)
					if (null != MFramework.Instance.Scene.GetEntityByName((m_lbEntityList.Items[iEntityIndex] as MEntity).Name))
					{// Compare for existing entities with same name (같은 이름을 가진 엔티티가 존재하는지 보고나서)
						// If you change the name (있으면 이름을 바꾸고)
						do
						{
							string kTempNameStr = m_pmScene.GetUniqueEntityName((m_lbEntityList.Items[iEntityIndex] as MEntity).Name + "_i");
							//while(null != m_pmScene.GetEntityByName((m_lbEntityList.Items[iEntityIndex] as MEntity).Name + "_i"))
							{
								(m_lbEntityList.Items[iEntityIndex] as MEntity).Name = kTempNameStr;
							}
							
						} while (null != MFramework.Instance.Scene.GetEntityByName((m_lbEntityList.Items[iEntityIndex] as MEntity).Name));
					}
					// Add (추가)
					MFramework.Instance.Scene.AddEntity(m_lbEntityList.Items[iEntityIndex] as MEntity, true);
					// If new selection set feature is turned on you can add entities to selection set (새 셀렉션셋 기능이 켜져있으면 새 셀렉션셋에도 엔티티 추가)
					if (true == m_bGetByNewSelSetName)
					{
						kNewSelSet.Name = kNewSelSetName;
						kNewSelSet.AddEntity(m_lbEntityList.Items[iEntityIndex] as MEntity);
					}
				}
			}

			if (false == m_bGetByNewSelSetName)
			{// If the ability to add new entities to a selection set is turned off (새 그룹으로 추가 기능이 꺼져있으면)
				for (int iSelSetIndex = 0; iSelSetIndex < m_lbSelectionSetList.Items.Count; ++iSelSetIndex)
				{// During all selection set (모든 셀렉션 셋중에..)
					if (true == m_lbSelectionSetList.GetSelected(iSelSetIndex))
					{// For the selected selection set (선택된 셀렉션셋에 대해)
						for (int iEntityIndex = 0; iEntityIndex < m_lbEntityList.Items.Count; ++iEntityIndex)
						{// For all entities (모든 엔티티들에 대해)
							if (null != (m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet).GetEntityByName(
								(m_lbEntityList.Items[iEntityIndex] as MEntity).Name))
							{// When the entity is in a selection set (해당 엔티티가 셀렉션셋에 있을 때)
								if (false == m_lbEntityList.GetSelected(iEntityIndex))
								{// If the entity is not selected (그 엔티티가 선택된 상태가 아니라면)
									// Remove from section set (셀렉션 셋에서 제거)
									(m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet).RemoveEntity(
										m_lbEntityList.Items[iEntityIndex] as MEntity);
								}
							}
						}
						if (null != MFramework.Instance.Scene.GetSelectionSetByName((
							m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet).Name))
						{// Reports if a selection set with same name exists (같은 이름을 가진 셀렉션 셋이 존재하는지 보고)
							// If there is a name change (있으면 이름을 바꿈)
							do
							{
								string kTempNameStr = m_pmScene.GetUniqueSelectionSetName((m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet).Name + "_i");
								(m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet).Name = kTempNameStr;
							} while (null != MFramework.Instance.Scene.GetSelectionSetByName((m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet).Name));
							
						}
						if (1 <= (m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet).EntityCount)
						{// If there is more than one entity in the selection set that has been processed above (위에서 처리가 끝난 셀렉션 셋에 엔티티가 하나이상 있으면)
							// Add (추가)
							MFramework.Instance.Scene.AddSelectionSet(m_lbSelectionSetList.Items[iSelSetIndex] as MSelectionSet);
						}
					}
				}
			}
			else
			{// If the new selection set add-on is turned on (새 셀렉션셋 추가 기능이 켜져 있으면)
				if (null != MFramework.Instance.Scene.GetSelectionSetByName(kNewSelSetName))
				{// Reports whether the new selection set name already exists (새 셀렉션셋이름이 이미 존재하는지 보고)
					// Rename if present (존재하면 이름을 바꿈)
					do
					{
						string kTempNameStr = m_pmScene.GetUniqueSelectionSetName(kNewSelSet.Name + "_i");
						kNewSelSet.Name = kTempNameStr;
					} while (null != MFramework.Instance.Scene.GetSelectionSetByName(kNewSelSet.Name));
				}
				// Add a new set (새 셋 추가)
				if(1<=kNewSelSet.EntityCount)
				{
					MFramework.Instance.Scene.AddSelectionSet(kNewSelSet);
				}
			}

			this.Close();
		}

		private void m_btnCancel_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		#region EntityComparer class
		private class EntityComparer : IComparer
		{
			#region IComparer Members
			public int Compare(object pmObjectA, object pmObjectB)
			{
				MEntity pmEntityA = pmObjectA as MEntity;
				MEntity pmEntityB = pmObjectB as MEntity;
				if (pmEntityA == null || pmEntityB == null)
				{
					throw new ArgumentException("EntityComparer only " +
						"supports comparing MEntity instances.");
				}

				return pmEntityA.Name.CompareTo(pmEntityB.Name);
			}
			#endregion
		}
		#endregion

		#region SelectionSetComparer class
		private class SelectionSetComparer : IComparer
		{
			#region IComparer Members
			public int Compare(object pmObjectA, object pmObjectB)
			{
				MSelectionSet pmSelctionSetA = pmObjectA as MSelectionSet;
				MSelectionSet pmSelctionSetB = pmObjectB as MSelectionSet;
				if (pmSelctionSetA == null || pmSelctionSetB == null)
				{
					throw new ArgumentException("EntityComparer only " +
						"supports comparing MEntity instances.");
				}

				return pmSelctionSetA.Name.CompareTo(pmSelctionSetB.Name);
			}
			#endregion
		}
		#endregion

		// Matches selected items in SelectionSetListto those in EntriList (SelectionSetList에서 선택된 것들과 EntriList의 것들을 매칭시킴)
		private void m_lbSelectionSetList_SelectedIndexChanged(object sender, EventArgs e)
		{
			MSelectionSet[] kSelectoinSet = m_pmScene.GetSelectionSets();
			MSelectionSet kSelectedSet = null;
			m_lbEntityList.ClearSelected();
			
			for (int iSelectionSetIndex = 0; iSelectionSetIndex < kSelectoinSet.Length; ++iSelectionSetIndex)
			{
				if (true == m_lbSelectionSetList.GetSelected(iSelectionSetIndex))
				{
					kSelectedSet = m_lbSelectionSetList.Items[iSelectionSetIndex] as MSelectionSet;
					MEntity[] kEntities = kSelectedSet.GetEntities();

					m_lbEntityList.BeginUpdate();
					for(int iListIndex=0 ; iListIndex < m_lbEntityList.Items.Count ; ++iListIndex)
					{// For every element in the entry list box (엔트리 리스트박스에 들어있는 모든 요소에 대해)
						for (int iEntityIndex = 0; iEntityIndex < kEntities.Length; ++iEntityIndex)
						{// For every element in the entity array
							// Is the upper-entry array [iEntityIndex].Name equal to [iListIndex].Name? (위 엔트리 배열[iEntityIndex].Name과 리스트박스요소[iListIndex].name이 같은가?)
							if (kEntities[iEntityIndex].Name == (m_lbEntityList.Items[iListIndex] as MEntity).Name)
							{// If it is the same select box element [iListIndex] (같으면 리스트박스요소[iListIndex]를 선택상태로...)
								m_lbEntityList.SetSelected(iListIndex, true);
							}							
						}						
					}
					m_lbEntityList.EndUpdate();
				}
			}
		}

		private void m_lbEntityList_SelectedIndexChanged(object sender, EventArgs e)
		{
			m_iSectectedEntityCount = 0;
			for (int iIndex = 0; iIndex < m_lbEntityList.Items.Count; ++iIndex)
			{
				if (m_lbEntityList.GetSelected(iIndex))
				{
					++m_iSectectedEntityCount;
				}
			}
		}

		private void m_cbGetByNewSelectionSet_CheckedChanged(object sender, EventArgs e)
		{
			m_bGetByNewSelSetName = !m_bGetByNewSelSetName;
			if (true == m_bGetByNewSelSetName)
			{
				m_tbNewSelectionSet.Show();
			}
			else
			{
				m_tbNewSelectionSet.Hide();
			}
		}
	}
}
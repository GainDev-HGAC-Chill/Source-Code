namespace Emergent.Gamebryo.SceneDesigner.GUI.ProjectG
{
	partial class XmlPropertiesPanel
	{
		/// <summary>
		/// Required designer variable (필수 디자이너 변수입니다.)
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up all resource that are in use (사용 중인 모든 리소스를 정리합니다.)
		/// </summary>
		/// <param name="disposing">Set to true if managed resources should be deleted, otherwise to false.</param> (<param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>)
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer-Generated Code // 디자이너에서 생성한 코드

		/// <summary>
		/// This method is required for designer support (디자이너 지원에 필요한 메서드입니다.)
		/// Do not modify the contents of this method with the code editor (이 메서드의 내용을 코드 편집기로 수정하지 마십시오.)
		/// </summary>
		private void InitializeComponent()
		{
			this.m_gridProperties = new System.Windows.Forms.PropertyGrid();
			this.SuspendLayout();
			// 
			// m_gridProperties
			// 
			this.m_gridProperties.Dock = System.Windows.Forms.DockStyle.Fill;
			this.m_gridProperties.LineColor = System.Drawing.SystemColors.ScrollBar;
			this.m_gridProperties.Location = new System.Drawing.Point(0, 0);
			this.m_gridProperties.Name = "m_gridProperties";
			this.m_gridProperties.Size = new System.Drawing.Size(285, 383);
			this.m_gridProperties.TabIndex = 1;
			this.m_gridProperties.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.m_gridProperties_PropertyValueChanged);
			// 
			// XmlPropertiesPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(285, 383);
			this.Controls.Add(this.m_gridProperties);
			this.Name = "XmlPropertiesPanel";
			this.Text = "Xml Properties";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.PropertyGrid m_gridProperties;
	}
}
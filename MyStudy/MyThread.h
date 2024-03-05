#pragma once
namespace MyThead {
	void Main();
	/// <summary>
	/// thread
	/// </summary>
	void case1();

	/// <summary>
	/// mutex
	/// </summary>
	void case2();

	/// <summary>
	/// condition_variable
	/// </summary>
	void case3();

	/// <summary>
	/// atomic
	/// </summary>
	void case4();

	/// <summary>
	/// relaxed ordering
	/// </summary>
	void case5();

	/// <summary>
	/// relaxed and release - acquire ordering
	/// </summary>
	void case6();

	/// <summary>
	/// release - acquire ordering
	/// </summary>
	void case7();

	/// <summary>
	/// Sequentially-consistent ordering
	/// </summary>
	void case8();

	/// <summary>
	/// <para>coherence-ordered-before </para>
	/// it's about Sequentially-consistent ordering when seq_cst are mixed with other memory order
	/// </summary>
	void case9();

	/// <summary>
	/// promise
	/// </summary>
	void case10();

	/// <summary>
	/// promise exception
	/// </summary>
	void case11();
	
	/// <summary>
	/// waitfor
	/// </summary>
	void case12();
	
	/// <summary>
	/// shared_future
	/// </summary>
	void case13();

	/// <summary>
	/// packaged_task
	/// </summary>
	void case14();

	/// <summary>
	/// async
	/// </summary>
	void case15();
}


<h1> Лабораторная работа №3 </h1>
<h2>  Тема: Основы обектно-ориентированного программирования и проектирование UML-диаграмм </h2>
<h3>Выполнил:</h3>
Студент <u>2</u> курса группы <u>Пиж-б-о-23-2(2)</u>
Направление подготовки: <u>09.03.04 Программная инженерия</u>
Форма обучения: <u>Очная.</u>
<u>Фуфаев Никита Александрович</u>

<h3>Задание 2:</h3>
<h4>Пиццерия</h4>
<p>Пиццерия предлагает клиентам три вида пиццы: Пепперони, Барбекю и Дары Моря, каждая из которых определяется тестом, соусом и начинкой.</p>
<p>Требуется спроектировать и реализовать приложение для терминала, позволяющее обеспечить обслуживание посетителей.</p>
<p>В бизнес-процессе работы пиццерии в контексте задачи можно выделить 3 сущности (объекта):</p>
<p>Терминал: отвечает за взаимодействие с пользователем:</p>
<p>- вывод меню на экран;</p>
<p>- прием команд от пользователя (выбор пиццы, подтверждение заказа, оплата и др.).</p>
<p>Заказ: содержит список заказанных пицц, умеет подсчитывать свою стоимость;</p>
<p>Пицца: содержит заявленные характеристики пиццы, а также умеет себя подготовить (замесить тесто, собрать ингредиенты и т.д.), испечь, порезать и упаковать.</p>
<p>Т.к. пиццерия реализует несколько видов пиццы, которые различаются характеристиками, логично будет сделать общий класс Пицца, 
  а в дочерних классах (например, классе ПиццаБарбекю) уточнить характеристики конкретной пиццы.</p>

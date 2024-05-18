-- Generate Restrictions
create procedure GenerateRestrictions()
begin
drop table if exists Restrictions;
create temporary table Restrictions(RowIndex int not null, Coefficient float not null);
insert into Restrictions (
    select id as RowIndex, quantity as Coefficient
    from Materials
    union
    select id + (select count(id) from Materials) as RowIndex, case when isnull(total) then 0 else total end as Coefficient
    from (
        select product_id, sum(count) as total
        from Orders
        group by product_id
        order by product_id
    ) as opd
    right outer join ProductNames as pn
    on opd.product_id = pn.id
    order by RowIndex
);
end

-- Generate Entries
create procedure GenerateEntries()
begin drop table if exists Entries;
create temporary table Entries(RowIndex int not null, ColumnIndex int not null, Coefficient float not null);
insert into Entries (
    select pd.material_id as RowIndex, pd.id as ColumnIndex, pd.quantity as Coefficient
    from ProductNames as pn
    join Products as pd
    on pn.id = pd.id
    union
    select id + (select count(id) from Materials) as RowIndex, id as ColumnIndex, 1 as Coefficient
    from ProductNames
    order by RowIndex
);
end

-- Generate Cost Function
create procedure GenerateCostFunction()
begin drop table if exists CostFunction;
create temporary table CostFunction(ColumnIndex int not null, Coefficient float not null);
insert into CostFunction (
    select id as ColumnIndex, -1 as Coefficient
    from ProductNames
);
end

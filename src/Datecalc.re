let today = String.sub(Js.Date.toISOString(Js.Date.make()), 0, 10);

[@react.component]
let make = () => {
  let (from, setFrom) = Form.useInput(today);
  let (adjustment, setAdjustment) = Form.useInput(0);
  let (freq, setFreq) = Form.useInput("W");
  let (dateStart, setDateStart) = Form.useInput(today);
  let (dateEnd, setDateEnd) = Form.useInput(today);

  let date = Js.Date.fromString(from);
  let dateString =
    Js.Date.setDate(
      date,
      Js.Date.getDate(date)
      +. float_of_int(adjustment * (freq == "W" ? 7 : 1)),
    )
    -> Js.Date.fromFloat
    -> Js.Date.toDateString;
  let dateDiff =
    Js.Date.valueOf(Js.Date.fromString(dateEnd))
    -. Js.Date.valueOf(Js.Date.fromString(dateStart));
  let dateDiffString =
    string_of_int(truncate(dateDiff /. 86400000.)) ++ " days";

  <div className="container">
    <h1> {React.string("Date Calculator")} </h1>
    <div className="heading">
      {React.string("Add days/weeks to a date")}
    </div>
    <div className="row">
      <input
        type_="date"
        value=from
        onChange={setFrom}
      />
      <input
        type_="number"
        value={string_of_int(adjustment)}
        onChange={setAdjustment}
      />
      <select onChange={setFreq} value=freq>
        <option value="D"> {React.string("Days")} </option>
        <option value="W"> {React.string("Weeks")} </option>
      </select>
    </div>
    <div className="output"> {React.string(dateString)} </div>
    <div className="heading">
      {React.string("Number of days between two dates")}
    </div>
    <div className="row">
      <input
        type_="date"
        value=dateStart
        onChange={setDateStart}
      />
      <input
        type_="date"
        value=dateEnd
        onChange={setDateEnd}
      />
    </div>
    <div className="output"> {React.string(dateDiffString)} </div>
  </div>;
};

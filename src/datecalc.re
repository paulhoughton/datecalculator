type state = {
  from: string,
  adjustment: int,
  freq: string,
  dateStart: string,
  dateEnd: string
};

type action =
  | SetDate(string)
  | SetDateStart(string)
  | SetDateEnd(string)
  | SetAdjustment(string)
  | SetFreq(string);

let component = ReasonReact.reducerComponent("DateApp");

let str = ReasonReact.stringToElement;

let valueFromEvent = event => ReactDOMRe.domElementToObj(
                                ReactEventRe.Form.target(event)
                              )##value;

let today = String.sub(Js.Date.toISOString(Js.Date.make()), 0, 10);

let make = _children => {
  ...component,
  initialState: () => {
    from: today,
    adjustment: 0,
    freq: "W",
    dateStart: today,
    dateEnd: today
  },
  reducer: (action, state) =>
    switch action {
    | SetDate(newValue) => ReasonReact.Update({...state, from: newValue})
    | SetDateStart(newValue) =>
      ReasonReact.Update({...state, dateStart: newValue})
    | SetDateEnd(newValue) => ReasonReact.Update({...state, dateEnd: newValue})
    | SetAdjustment(newValue) =>
      ReasonReact.Update({...state, adjustment: int_of_string(newValue)})
    | SetFreq(newValue) => ReasonReact.Update({...state, freq: newValue})
    },
  render: ({state: {from, adjustment, freq, dateStart, dateEnd}, reduce}) => {
    let date = Js.Date.fromString(from);
    let dateString =
      Js.Date.setDate(
        date,
        Js.Date.getDate(date)
        +. float_of_int(adjustment * (freq == "W" ? 7 : 1))
      )
      |> Js.Date.fromFloat
      |> Js.Date.toDateString;
    let dateDiff =
      Js.Date.valueOf(Js.Date.fromString(dateEnd))
      -. Js.Date.valueOf(Js.Date.fromString(dateStart));
    let dateDiffString =
      string_of_int(truncate(dateDiff /. 86400000.)) ++ " days";
    <div className="container">
      <h1> (str("Date Calculator")) </h1>
      <div className="heading"> (str("Add days/weeks to a date")) </div>
      <div className="row">
        <input
          _type="date"
          value=from
          onChange=(reduce(evt => SetDate(valueFromEvent(evt))))
        />
        <input
          _type="number"
          value=(string_of_int(adjustment))
          onChange=(reduce(evt => SetAdjustment(valueFromEvent(evt))))
        />
        <select
          onChange=(reduce(evt => SetFreq(valueFromEvent(evt)))) value=freq>
          <option value="D"> (str("Days")) </option>
          <option value="W"> (str("Weeks")) </option>
        </select>
      </div>
      <div className="output"> (str(dateString)) </div>
      <div className="heading">
        (str("Number of days between two dates"))
      </div>
      <div className="row">
        <input
          _type="date"
          value=dateStart
          onChange=(reduce(evt => SetDateStart(valueFromEvent(evt))))
        />
        <input
          _type="date"
          value=dateEnd
          onChange=(reduce(evt => SetDateEnd(valueFromEvent(evt))))
        />
      </div>
      <div className="output"> (str(dateDiffString)) </div>
    </div>;
  }
};
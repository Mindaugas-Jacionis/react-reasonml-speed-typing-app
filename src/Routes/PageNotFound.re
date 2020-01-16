let component = ReasonReact.statelessComponent("PageNotFound");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      {ReasonReact.string("Oooops! Page Stolen by monkeys 🙈🙊🙉")}
    </div>,
};